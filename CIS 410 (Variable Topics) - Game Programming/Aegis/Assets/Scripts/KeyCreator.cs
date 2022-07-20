using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class KeyCreator : MonoBehaviour
{
    // This script is designed to be attached to something in the scene that acts as
    // an observer. I simply create an empty object and attach the script to it

    public int enemiesNeeded; // Number of gold enemies the player needs to defeat to spawn object (set in inspector)
    static public int enemiesDefeated; // Number of enemies the player has defeated
    private GameObject victoryItem; // Actual victoryItem to be spawned
    private GameObject victoryText;
    private bool alreadySpawned; // Want to make sure we only spawn one object

    void Start()
    {
      victoryItem = GameObject.FindGameObjectWithTag("Key");
      victoryText = GameObject.FindGameObjectWithTag("specific tag");
      // Initialize set the victory item to false
      victoryItem.SetActive(false);
      victoryText.SetActive(false);

      // Instantiate the number of enemies defeated to 0
      enemiesDefeated = 0;

      alreadySpawned = false;
    }

    void Update()
    {
      if((enemiesDefeated >= enemiesNeeded) && (alreadySpawned == false))
      {
        Debug.Log("Victory Item Spawned");
        victoryItem.gameObject.SetActive(true);
        victoryText.SetActive(true);
        alreadySpawned = true;
      }
    }
}
