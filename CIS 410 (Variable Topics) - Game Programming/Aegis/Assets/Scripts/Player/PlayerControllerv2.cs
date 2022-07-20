using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UI;
using TMPro;

// Movement from Brackeys: https://www.youtube.com/watch?v=4HpC--2iowE
public class PlayerControllerv2 : MonoBehaviour
{

  public CharacterController controller;
  public Transform cam;
  public float speed = 6f;
  public float smoothTurn = 0.1f;
  public static float invincTime = 1.5f;
  public static float currInvincTime = 0.0f;
  public static float flashTime = 0.0f;
  float turnSmoothVelocity;
  private GameObject uiPrefab;
  public Vector3 moveDir;
  public LinkedList<Image> hearts;
  public GameObject powerup;
  public List<Renderer> renderers;
  [SerializeField] private List<SelectableEnemies> selectables;
  [SerializeField] private List<SelectableEnemies> frozen_enemies;
  private float frozen_timer;
  private bool shockwave = false;
  private bool freeze = false;
  public TextMeshProUGUI powerUpText;
  private float xDisplacement = 35;
  public static bool enemyHit;
  public static bool invincible = false;
  public static int lives;
  private Animator animator;
  static float keyCount;

    void Start()
    {
      lives = 3;
      //Debug.Log(powerUpText);
      // create the hearts linked-list
      hearts = new LinkedList<Image>();
      // get the two images
      var image = GameObject.FindGameObjectWithTag("image");

      // get the UIPrefab gameobject
      uiPrefab = GameObject.Find("UIPrefab");

      // get the powerUpText gameobject
      powerUpText = uiPrefab.transform.Find("Canvas").transform.Find("PowerUpText").GetComponent<TextMeshProUGUI>();

      // add the first image (heart) to a list of hearts
      hearts.AddLast(image.GetComponent<Image>());

      animator = GetComponent<Animator>();
      var renders = GetComponentsInChildren<Renderer>();
      // renders[1] is the body, renders[2] is the head
      renderers.Add(renders[1]);
      renderers.Add(renders[2]);

      SetPowerUpText();

      // instantiate and draw 2 more hearts to make 3
      InitializeLives();
    }

    public void SetPowerUpText()
    {
      // sets the powerUpText
      powerUpText.text = $"<u>Power Up</u>\n{(shockwave ? "Shockwave" : freeze ? "Freeze" : "None")}\n";
    }

    void InitializeLives()
    {
      for (int i = 0; i < lives - 1; ++i)
      {
        // instantiate (copy) the first heart and make it a child of canvas (the first child of uiPrefab)
        Image newHeart = Image.Instantiate(hearts.First(), uiPrefab.transform.GetChild(0));
        // add the new image to the hearts linked-list
        hearts.AddLast(newHeart);
        // change the new heart's position and set it to be active
        hearts.Last().GetComponent<RectTransform>().anchoredPosition += new Vector2(xDisplacement, 0);
        hearts.Last().gameObject.SetActive(true);
        // the next heart will be 35 pixels to the right
        xDisplacement += 35;
      }
    }

    void AddLives()
    {
      // instantiate (copy) the first heart and make it a child of canvas (the first child of uiPrefab)
      Image newHeart = Image.Instantiate(hearts.First(), uiPrefab.transform.GetChild(0));
      // add the new image to the hearts linked-list
      hearts.AddLast(newHeart);
      // change the new heart's position and set it to be active
      hearts.Last().GetComponent<RectTransform>().anchoredPosition += new Vector2(xDisplacement, 0);
      hearts.Last().gameObject.SetActive(true);
      // the next heart will be 35 pixels to the right, add 1 life
      xDisplacement += 35;
      lives += 1;
    }

    void RemoveLives()
    {
      // destroy the last heart object that was create and remove it from the hearts list
      Destroy(hearts.Last());
      hearts.RemoveLast();
      // put the displacement back to where it was before, remove 1 life
      xDisplacement -= 35;
    }

    // Update is called once per frame
    void Update()
    {
      // Locks cursor once the screen is clicked.
      Cursor.lockState = CursorLockMode.Locked;

      float horizontal = Input.GetAxisRaw("Horizontal");
      float vertical = Input.GetAxisRaw("Vertical");

      bool hasHorizontalInput = !Mathf.Approximately(horizontal, 0f);
      bool hasVerticalInput = !Mathf.Approximately(vertical, 0f);
      bool isWalking = (hasHorizontalInput || hasVerticalInput) && !ThirdPersonDash.inDash;

      animator.SetBool("IsWalking", isWalking);

      Vector3 direction = new Vector3(horizontal, 0f, vertical).normalized;

      float targetAngle = Mathf.Atan2(direction.x, direction.z) * Mathf.Rad2Deg + cam.eulerAngles.y;
      float angle = Mathf.SmoothDampAngle(transform.eulerAngles.y, targetAngle, ref turnSmoothVelocity, smoothTurn);
      transform.rotation = Quaternion.Euler(0f, angle, 0f);

      if(direction.magnitude >= 0.1f)
      {
        moveDir = Quaternion.Euler(0f, targetAngle, 0f) * Vector3.forward;
        Vector3 mvmt = moveDir.normalized * speed * Time.deltaTime;
        if (Input.GetKey(KeyCode.LeftShift))
        {
            Debug.Log("Left shift pressed!");
            mvmt *= 1.8f;
        }
        controller.Move(mvmt);
      }

      // adds 1.5 seconds of i-frames when hit
      if (invincible)
      {
          currInvincTime += Time.deltaTime;
          if (currInvincTime >= invincTime)
          {
              invincible = false;
              currInvincTime = 0;
          }
      }

        // shockwave power up attack
        if (Input.GetMouseButtonDown(1) && (shockwave == true))
        {
            Debug.Log("Shockwave used!");
            shockwave = false;
            SetPowerUpText();
            // force for pushing back
            float force = 750.0f;

            // detect enemies in a given range of the player
            float range = 10.0f;
            for (int i = 0; i < selectables.Count; i++)
            {
                // check for null
                if (selectables[i] == null)
                {
                    selectables.Remove(selectables[i]);
                }
                else
                {
                    var distance = Vector3.Distance(selectables[i].transform.position, transform.position);
                    if (distance <= range)
                    {
                        // Calculate Angle Between the collision point and the player
                        Vector3 dir = selectables[i].transform.position - transform.position;

                        // add force in the direction of dir and multiply it by force.
                        selectables[i].rb.AddForce(dir * force);
                    }
                }
            }
            shockwave = false;
        }
        else if (Input.GetMouseButtonDown(1) && (freeze == true))
        {
            Debug.Log("Freeze used!");
            frozen_timer = 5.0f;
            freeze = false;
            SetPowerUpText();
            // get all enemies within range
            float range = 10.0f;
            for (int i = 0; i < selectables.Count; i++)
            {
                // check for null
                if (selectables[i] == null)
                {
                    selectables.Remove(selectables[i]);
                }
                else
                {
                    var distance = Vector3.Distance(selectables[i].transform.position, transform.position);
                    if (distance <= range)
                    {
                        // add enemy to the frozen list
                        frozen_enemies.Add(selectables[i]);
                        // freeze enemy
                        Debug.Log("Freezing");
                        if (selectables[i].CompareTag("enemy"))
                        {
                            selectables[i].GetComponent<SlimeAI_v2>().enabled = false;
                        }
                        if (selectables[i].CompareTag("shooter"))
                        {
                            selectables[i].GetComponent<ShooterAI>().enabled = false;
                        }
                        if (selectables[i].CompareTag("sniper"))
                        {
                            selectables[i].GetComponent<SniperAi>().enabled = false;
                        }
                        if (selectables[i].CompareTag("expander"))
                        {
                            selectables[i].GetComponent<expander_ai>().enabled = false;
                        }
                        if (selectables[i].CompareTag("Key Enemy"))
                        {
                            selectables[i].GetComponent<KeyholderLogic>().enabled = false;
                        }
                    }
                }
            }
        }
        // wait 3 seconds
        if ((frozen_enemies.Count >= 1) && (frozen_timer <= 0.0f))
        {
            Debug.Log("Unfreezing");
            // unfreeze enemies
            for (int i = 0; i < frozen_enemies.Count; i++)
            {
                if (frozen_enemies[i].CompareTag("enemy"))
                {
                    frozen_enemies[i].GetComponent<SlimeAI_v2>().enabled = true;
                }
                if (frozen_enemies[i].CompareTag("shooter"))
                {
                    frozen_enemies[i].GetComponent<ShooterAI>().enabled = true;
                        }
                if (frozen_enemies[i].CompareTag("sniper"))
                {
                    frozen_enemies[i].GetComponent<SniperAi>().enabled = true;
                        }
                if (frozen_enemies[i].CompareTag("expander"))
                {
                    frozen_enemies[i].GetComponent<expander_ai>().enabled = true;
                        }
                if (frozen_enemies[i].CompareTag("Key Enemy"))
                {
                    frozen_enemies[i].GetComponent<KeyholderLogic>().enabled = true;
                }
                // remove from frozen list
                frozen_enemies.Remove(frozen_enemies[i]);
            }
        }
        else if(frozen_timer >= 0.0)
        {
            //Debug.Log("Waiting to unfreeze");
            frozen_timer -= Time.deltaTime;
        }

      // Return to menu
      if (Input.GetKey(KeyCode.Backslash))
      {
        SceneManager.LoadScene("Title");
      }
    }

    // function ran when you take damage
    private void TakeDamage()
    {
        Debug.Log("Hit by enemy!");
        if(lives > 0 && !invincible)
        {
            lives -= 1;
            flashTime = 0;
            // flash Shieldon a color to signify damage (coroutine since flashing is independent of game state)
            StartCoroutine(DamageFlash());
            invincible = true;
            RemoveLives();
        }
    }

    IEnumerator DamageFlash()
    {
        // t is the normalized value of time based on time range, since we want it to flash red then white then red
        float t;
        while (flashTime < invincTime)
        {
            flashTime += Time.deltaTime;
            // flash red to white
            if (flashTime < 0.5f)
            {
                // normalize flashTime depending on the range
                t = flashTime * 2;
                // lambda expression to lerp for each renderer (body and head)
                // same thing for the other conditional statements
                renderers.ForEach(r => r.material.color = Color.Lerp(Color.red, Color.white, t));
            }
            // flash white to red
            else if (flashTime >= 0.5 && flashTime <= 1)
            {
                t = (flashTime - 0.5f) * 2;
                renderers.ForEach(r => Color.Lerp(Color.white, Color.red, t));
            }
            // flash red to white
            else
            {
                t = (flashTime - 1f) * 2;
                renderers.ForEach(r => r.material.color = Color.Lerp(Color.red, Color.white, t));
            }
            yield return null;
        }

    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("Shockwave"))
        {
            other.gameObject.SetActive(false);
            shockwave = true;
            SetPowerUpText();
        }

        if(other.gameObject.CompareTag("Freeze"))
        {
            other.gameObject.SetActive(false);
            freeze = true;
            SetPowerUpText();
        }

        if (other.gameObject.CompareTag("Health "))
        {
            other.gameObject.SetActive(false);
            AddLives();
        }

        if(other.gameObject.CompareTag("Key"))
        {
        }

        // Projectiles use trigger colliders so they have to be tracked in
        // OnTriggerEnter
        if(other.gameObject.CompareTag("Projectile"))
        {
            TakeDamage();
        }
    }

    private void OnCollisionEnter(Collision other)
    {
      if (other.gameObject.CompareTag("enemy") || other.gameObject.CompareTag("sniper") || other.gameObject.CompareTag("shooter") || other.gameObject.CompareTag("expander"))
      {
            TakeDamage();
            // get the angle between the enemy and player
            Vector3 ang = (other.transform.position - transform.position);
            ang.y = 0;
            // apply a small force back on the enemy
            other.gameObject.GetComponent<Rigidbody>().AddForce(ang.normalized * 2.5f, ForceMode.Impulse);
      }
    }
}
