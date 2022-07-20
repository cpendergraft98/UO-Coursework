using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LookAtPlayer : MonoBehaviour
{
    GameObject Player;
    void Start()
    {
      Player = GameObject.FindGameObjectWithTag("Player");
    }
    void Update()
    {
      transform.rotation = Quaternion.LookRotation(transform.position - Player.transform.position);
    }
}
