using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class Victory : MonoBehaviour
{
  void OnTriggerEnter(Collider other)
  {
    if(other.gameObject.CompareTag("Player"))
    {
      Scene scene = SceneManager.GetActiveScene();

      switch(scene.name)
      {
        case "level1 Desert":
          SceneManager.LoadScene("Level1Transition");
          break;
        case "level2 forest":
          SceneManager.LoadScene("Level2Transition");
          break;
        case "level3 Cliffs":
          SceneManager.LoadScene("Victory");
          break;
        default:
          SceneManager.LoadScene("Title");
          break;
      }
    }
  }
}
