using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ClosePanel : MonoBehaviour {

    public string panel_name;
    public void OnMouseDown()
    {
        Manager.ui_manager.ClosePanel(panel_name);
    }
}
