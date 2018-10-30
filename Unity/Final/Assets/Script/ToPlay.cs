using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
public class ToPlay : MonoBehaviour {

	public void ToEnterPlayScene()
    {
        SceneManager.LoadScene("play");
        Manager.ui_manager.ClosePanel("loading");
    }
}
