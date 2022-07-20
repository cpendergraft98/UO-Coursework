using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;

public class Death : MonoBehaviour
{
    private int lives;
    public AudioSource DamageAudio;

    void Start()
    {
        lives = PlayerControllerv2.lives;
    }

    // Update is called once per frame
    void Update()
    {
        int currentLives = PlayerControllerv2.lives;
        if (currentLives != lives)
        {
            Debug.Log("Lives changed!");
            DamageAudio.Play();
            lives = currentLives;
        }
        if (lives <= 0)
        {
            //Debug.Log("Returning to title, game over!");
            DeathScreen();
        }
    }

    void DeathScreen()
    {
        SceneManager.LoadScene("Death");
    }
}
