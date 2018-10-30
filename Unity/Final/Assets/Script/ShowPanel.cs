using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ShowPanel : MonoBehaviour {

    public string show_panel;
	public void OnMouseDown()
    {
        if(UnityEngine.EventSystems.EventSystem.current.IsPointerOverGameObject()==false)
            Manager.ui_manager.ShowPanel(show_panel);
    }
}
