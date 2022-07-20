using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayMenuMusic : MonoBehaviour
{
    // Makes menu music play between menu scenes
    void Start()
    {
        GameObject.FindGameObjectWithTag("MenuMusic").GetComponent<MenuMusicController>().PlayMusic();
    }

}
