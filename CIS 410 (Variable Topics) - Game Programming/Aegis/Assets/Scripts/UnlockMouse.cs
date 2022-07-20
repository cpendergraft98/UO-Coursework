using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UnlockMouse : MonoBehaviour
{
    // Unlocks cursor in a UI scene
    void Update()
    {
      Cursor.lockState = CursorLockMode.Confined;
    }

}
