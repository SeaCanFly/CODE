using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class GoToScene : MonoBehaviour {

    public string scene_name;
    public void OnMouseDown()
    {
        if(UnityEngine.EventSystems.EventSystem.current.IsPointerOverGameObject()==false)
         SceneManager.LoadScene(scene_name);
    }

}
