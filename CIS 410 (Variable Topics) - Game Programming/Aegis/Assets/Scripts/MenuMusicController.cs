using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MenuMusicController : MonoBehaviour
{
    private AudioSource _MenuMusic;
    private GameObject[] OtherSources;
    private bool NotFirst = false;

    // Start is called before the first frame update
    void Start()
    {
        // This iterative logic makes sure that the music is not played
        // duplicated if returning to the title screen (DontDestroyOnLoad will
        // cause a new Music object to be duplicated every time the title
        // scene is loaded).
        OtherSources = GameObject.FindGameObjectsWithTag("MenuMusic");

        foreach (GameObject oneOther in OtherSources)
        {
          if(oneOther.scene.buildIndex == -1)
          {
            NotFirst = true;
          }
        }

        if(NotFirst == true)
        {
          Destroy(gameObject);
        }

        DontDestroyOnLoad(transform.gameObject);
        _MenuMusic = GetComponent<AudioSource>();
    }

    public void PlayMusic()
    {
      if(_MenuMusic.isPlaying)
      {
        return;
      }

      _MenuMusic.Play();
    }

    public void StopMusic()
    {
      _MenuMusic.Stop();
    }
}
