using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SniperProjectile : MonoBehaviour
{
    //GameObject player;
    private float speed = 15.0f;
    private float travel_time = 5.5f;

    // Start is called before the first frame update
    void Start()
    {
       // player = GameObject.FindGameObjectWithTag("Player");
    }

    // Update is called once per frame
    void Update()
    {
        // get the angle between the projectile and player
        //Vector3 flightPath = player.transform.position - transform.position;
        // apply force to the projectile
        //this.GetComponent<Rigidbody>().AddForce(flightPath * speed);

        transform.Translate(0, 0, speed * Time.deltaTime);
        if (travel_time <= 0.0f)
        {
            Destroy(this.gameObject);
        }
        else
        {
            travel_time -= Time.deltaTime;
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        Destroy(this.gameObject);
    }
}
