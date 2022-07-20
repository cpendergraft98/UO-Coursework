using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Navigation : MonoBehaviour
{
    public GameObject Camera;
    public GameObject TargetObject;
    void Update()
    {
      // A vector pointing straight ahead from the camera
      Vector3 CamLook = Camera.transform.position;
      //CamLook.x = 0.0f;
      CamLook.y = 0.0f;
      //PlayerLook.z = 0.0f;

      // A vector pointing from the camera to the target object
      Vector3 Target = TargetObject.transform.position - CamLook;
      //Target.x = 0.0f;
      Target.y = 0.0f;
      //Target.z = 0.0f;

      float roto = Vector3.Angle(CamLook, Target);
      Quaternion rotation = Quaternion.Euler(roto, 0, roto);

      transform.rotation = Quaternion.Slerp(transform.rotation, rotation, Time.deltaTime * 5.0f);

    }
}
