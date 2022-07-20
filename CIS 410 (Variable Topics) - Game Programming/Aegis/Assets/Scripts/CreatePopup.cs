using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CreatePopup : MonoBehaviour
{
    public GameObject popup;

    void Start()
    {
      popup.SetActive(false);
    }

    void OnTriggerEnter(Collider other)
    {
      if(other.gameObject.CompareTag("Player"))
      {
        popup.SetActive(true);
        //
      }
    }
}
