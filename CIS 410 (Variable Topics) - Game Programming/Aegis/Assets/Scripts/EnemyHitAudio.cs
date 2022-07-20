using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyHitAudio : MonoBehaviour
{
    void OnCollisionEnter(Collision other)
    {
      if(other.gameObject.CompareTag("enemy") || other.gameObject.CompareTag("sniper") || other.gameObject.CompareTag("shooter") || other.gameObject.CompareTag("expander") || other.gameObject.CompareTag("Key Enemy") )
      {
        if(!(GetComponent<AudioSource>().isPlaying))
        {
          GetComponent<AudioSource>().Play();
        }
      }
    }
}
