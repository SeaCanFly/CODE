using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bar : MonoBehaviour {

    private void Start()
    {
        Manager.cur_score = 0;
    }
    void Update () {
        if(Manager.cur_score<=300)
            transform.localPosition = new Vector2(-4 + Manager.cur_score*2,6);
	}
}
