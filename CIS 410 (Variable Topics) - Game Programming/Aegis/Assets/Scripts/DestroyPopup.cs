using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DestroyPopup : MonoBehaviour
{
    public GameObject popup;

    void OnTriggerEnter(Collider other)
    {
      if(other.gameObject.CompareTag("Player"))
      {
        popup.SetActive(false);
      }
    }
}
