using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using TMPro;

public class PlayerMovement : MonoBehaviour
{

    // Following four lines utilized in the field of vision. See SelectableEnemies.cs
    // to understand the SelectableEnemies behavior.
    [SerializeField] private List<SelectableEnemies> selectables;
    private Ray playerRay;
    private SelectableEnemies cmp;
    private RaycastHit hit;

    public float turnSpeed = 20f;

    Animator m_Animator;
    TextMeshPro m_Text;
    MeshRenderer m_Mesh;
    Rigidbody m_Rigidbody;
    AudioSource m_AudioSource;
    Vector3 m_Movement;
    Quaternion m_Rotation = Quaternion.identity;


    // Start is called before the first frame update
    void Start()
    {
        m_Animator = GetComponent<Animator>();
        m_Rigidbody = GetComponent<Rigidbody>();
        m_AudioSource = GetComponent<AudioSource>();

        // since the text component is a child of John Lemon themself, we have to use GetComponentInChildren to retrieve the component
        m_Text = GetComponentInChildren(typeof(TextMeshPro)) as TextMeshPro;
        // don't show the text on game start
        m_Text.enabled = false;
    }

    // Logic for field of vision *inspired* by https://www.youtube.com/watch?v=cxJnvEpwQHc
    // (our implementation ended up being quite different).
    // Determines which enemy requires the least rotation to be looking at
    public void fieldOfVision(Ray ray)
    {
      // Initialize to null whenever function is called
      cmp = null;
      // Iterate over all our "selectables" (enemies)
      for(int i = 0; i < selectables.Count; i++)
      {
        // Generate our first vector from the player ray
        var vector1 = ray.direction;

        // Generate the second ray using the player ray and the location of the
        // enemy being looked at.
        var vector2 = selectables[i].transform.position - ray.origin;

        // Get the hit info on the ray generated between the player and the
        // and the enemy [i]. If that ray hits a wall, we ignore because it
        // is not in line of sight.
        Physics.Raycast(ray.origin, vector2, out hit);

        if((hit.rigidbody != null) && (hit.rigidbody.tag == "Ghost"))
        {
            // Compute a "look percentage" by using the dot product
            var lookPercentage = Vector3.Dot(vector1.normalized, vector2.normalized);

            // Update the look percentage for each "selectable" (enemy)
            selectables[i].LookPercentage = lookPercentage;

            // Retain the enemy that will require the least rotation to be directly
            // in front of the player.
            if((cmp == null) && (lookPercentage < 0))
            {
              continue;
            }
            else if((cmp == null) || (lookPercentage > cmp.LookPercentage))
            {
              cmp = selectables[i];
            }
          }
          else
          {
            continue;
          }
      }
      // This is probably where you want to do the interpolation for the symbol?
      // cmp should store the enemy game object that requires the least player
      // rotation to be looking at so you should be able to interpolate between
      // their positions using that.

      if((cmp != null) && (cmp.LookPercentage >= 0.90))
      {
        Debug.Log("You can see " + cmp.name + " in front of you!!");
        // enable the ! notification
        m_Text.enabled = true;
        // get the distance from the enemy spotted and the player
        float distance = Vector3.Distance(m_Rigidbody.position, cmp.transform.position);
        Debug.Log($"Distance = {distance}!");
        // calculate the percent along two points t.
        // these numbers were determined by experimentation; these values allow yellow to notify caution, and allow *just* enough time for player to escape when it turns red.
        float t = (distance - 5.7f) / (3.7f - 5.7f);
        // set the text color to the lerped value between going to yellow to red as the enemy gets closer to the player
        m_Text.color = Color.Lerp(Color.yellow, Color.red, t);
      }
      else
      {
        Debug.Log("No enemies in sight.");
        m_Text.enabled = false;
        m_Text.color = Color.white;
      }

    }

    void FixedUpdate()
    {
        float horizontal = Input.GetAxis("Horizontal");
        float vertical = Input.GetAxis("Vertical");

        m_Movement.Set(horizontal, 0f, vertical);
        m_Movement.Normalize();

        bool hasHorizontalInput = !Mathf.Approximately(horizontal, 0f);
        bool hasVerticalInput = !Mathf.Approximately(vertical, 0f);
        bool isWalking = hasHorizontalInput || hasVerticalInput;
        m_Animator.SetBool("IsWalking", isWalking);

        if (isWalking)
        {
            if (!m_AudioSource.isPlaying)
            {
                m_AudioSource.Play();
            }
        }
        else
        {
            m_AudioSource.Stop();
        }

        Vector3 desiredForward = Vector3.RotateTowards(transform.forward, m_Movement, turnSpeed * Time.deltaTime, 0f);
        m_Rotation = Quaternion.LookRotation(desiredForward);

        // The following line *should* generate a ray originating at the player
        // and pointing in the direction he is facing (desiredForward)
        playerRay = new Ray(m_Rigidbody.position, desiredForward);

        // Call the fieldOfVision function to determine which (if any) enemy
        // objects are within the field of vision.
        fieldOfVision(playerRay);
    }

    void OnAnimatorMove()
    {
        m_Rigidbody.MovePosition(m_Rigidbody.position + m_Movement * m_Animator.deltaPosition.magnitude);
        m_Rigidbody.MoveRotation(m_Rotation);
    }
}
