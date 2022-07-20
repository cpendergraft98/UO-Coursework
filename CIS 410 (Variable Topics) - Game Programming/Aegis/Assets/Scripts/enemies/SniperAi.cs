using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class SniperAi : MonoBehaviour
{
    public NavMeshAgent snips;
    public Transform Player;
    public AudioSource shootAudio;

    [SerializeField] private GameObject ProjectilePrefab;
    private GameObject _Projectile;
    private float cooldownTimer;

    // Start is called before the first frame update
    void Start()
    { }

    // Update is called once per frame
    void Update()
    {
        var distance = Vector3.Distance(Player.position, transform.position);
        transform.LookAt(Player);

        // check for firing range
        if (distance < 48.0f)
        {
            if (cooldownTimer <= 0)
            {
                cooldownTimer = 2.0f;
                ShootAtPlayer();
            }
            cooldownTimer -= Time.deltaTime;
        }
    }

    void ShootAtPlayer()
    {
        Ray ray = new Ray(transform.position, transform.forward);
        RaycastHit hit;
        if (Physics.SphereCast(ray, 0.75f, out hit))
        {
            // create the starting position vector
            Vector3 start_pos = transform.TransformPoint(Vector3.forward * 1.5f);
            start_pos.y = start_pos.y + 1.2f;
            // play shooting audio
            shootAudio.Play();
            // instantiate the projectile 
            _Projectile = Instantiate(ProjectilePrefab) as GameObject;
            // Set the projectiles starting point
            _Projectile.transform.position = start_pos;
            // Set the projectiles rotation
            _Projectile.transform.rotation = transform.rotation;
        }
    }
}
