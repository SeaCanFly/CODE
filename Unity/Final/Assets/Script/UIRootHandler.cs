using UnityEngine;
public class UIRootHandler : MonoBehaviour
{
    void Start()
    {
        Manager.ui_manager.m_CanvasRoot = gameObject;
    }
}
