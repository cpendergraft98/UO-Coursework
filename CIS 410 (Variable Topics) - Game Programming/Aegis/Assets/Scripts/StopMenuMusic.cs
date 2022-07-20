using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StopMenuMusic : MonoBehaviour
{
    // Stops Menu Music from playing between scenes
    void Start()
    {
      GameObject.FindGameObjectWithTag("MenuMusic").GetComponent<MenuMusicController>().StopMusic();
    }
}
