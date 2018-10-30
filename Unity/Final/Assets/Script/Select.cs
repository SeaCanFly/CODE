using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Select : MonoBehaviour {

    bool on = true;
    IEnumerator select()
    {
        on = false;
        GetComponent<Renderer>().material.SetColor("_Color", new Color(1.0f, 1.0f, 1.0f, 0.5f));
        yield return new WaitForSeconds(1);
        GetComponent<Renderer>().material.SetColor("_Color", new Color(1.0f, 1.0f, 1.0f, 1.0f));
        on = true;
    }
    private void OnMouseDown()
    {
        if (Input.GetMouseButtonDown(0))
        {
            if (on)
            {
                StartCoroutine(select());
            }
        }
    }
    private void OnMouseOver()
    {
        if(Input.GetMouseButtonDown(1))
        {
            StartCoroutine(select());
        }
    }
}
