using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParticleController : MonoBehaviour
{
  public GameObject player;
  private ParticleSystem ps;
  bool m_IsPlayerAtExit;
    // Start is called before the first frame update
    void Start()
    {
      ps = GetComponent<ParticleSystem>();
      ps.Stop();
    }

    void OnTriggerEnter(Collider other)
    {
        if(other.gameObject == player)
        {
          ps.Play();
        }
    }
}
