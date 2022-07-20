using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CooldownBar : MonoBehaviour
{

    GameObject bar;
    LineRenderer barRenderer;

    // Start is called before the first frame update
    void Start()
    {
        // get the cooldown bar game object
        bar = GameObject.FindWithTag("CoolBar");
        // get the bar renderer from the bar object
        barRenderer = bar.GetComponent<LineRenderer>();
        // default the color to red and make the line invisible
        barRenderer.startColor = Color.red;
        barRenderer.endColor = Color.red;
        barRenderer.enabled = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (ThirdPersonDash.inCooldown)
        {
            // have the length of the bar be determined by the amount of time in the dash
            Vector3 newScale = new Vector3(1, 1, ThirdPersonDash.currTime);
            bar.transform.localScale = newScale;
            // make the bar visible
            barRenderer.enabled = true;
            // set the bar to the lerped color
            barRenderer.startColor = Color.Lerp(Color.red, Color.green, ThirdPersonDash.currTime);
            barRenderer.endColor = Color.Lerp(Color.red, Color.green, ThirdPersonDash.currTime);  
        }
        else 
        {
            // disable the bar if player is not dashing
            barRenderer.enabled = false;
        }
    }
}
