using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class GoScene : MonoBehaviour {

    public string scene_name;
    public void OnMouseDown()
    {
            SceneManager.LoadScene(scene_name);
    }
}
