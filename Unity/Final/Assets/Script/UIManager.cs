using UnityEngine;
using System.Collections.Generic;

public class UIManager
{
    private string UI_GAMEPANEL_ROOT = "";

    public GameObject m_CanvasRoot;

    public Dictionary<string, GameObject> m_PanelList = new Dictionary<string, GameObject>();



    private bool CheckCanvasRootIsNull()
    {
        if (m_CanvasRoot == null)
        {
            Debug.Log("m_CanvasRoot is Null");
            return true;
        }
        else
        {
            return false;
        }
    }

    private bool IsPanelLive(string name)
    {
        return m_PanelList.ContainsKey(name);
    }

    public GameObject ShowPanel(string name)
    {
        if (CheckCanvasRootIsNull())
            return null;

        if (IsPanelLive(name))
        {
            Debug.Log(name+" is Showing");
            return null;
        }

        GameObject loadGo = Resouce.ResourcesLoadCheckNull<GameObject>(UI_GAMEPANEL_ROOT + name);
        if (loadGo == null)
            return null;


        GameObject panel = Resouce.InstantiateGameObject(m_CanvasRoot, loadGo);
        panel.name = name;


        m_PanelList.Add(name, panel);


        return panel;
    }

    public void TogglePanel(string name, bool isOn)
    {
        if (IsPanelLive(name))
        {
            if (m_PanelList[name] != null)
                m_PanelList[name].SetActive(isOn);
        }
        else
        {
            Debug.Log("TogglePanel "+name+" not found.");
        }
    }

    public void ClosePanel(string name)
    {
        if (IsPanelLive(name))
        {
            if (m_PanelList[name] != null)
                Object.Destroy(m_PanelList[name]);

            m_PanelList.Remove(name);
        }
        else
        {
            Debug.Log("ClosePanel "+name+" not found.");
        }
    }

    public void CloseAllPanel()
    {
        foreach (KeyValuePair<string, GameObject> item in m_PanelList)
        {
            if (item.Value != null)
                Object.Destroy(item.Value);
        }

        m_PanelList.Clear();
    }

    public Vector2 GetCanvasSize()
    {
        if (CheckCanvasRootIsNull())
            return Vector2.one * -1;

        RectTransform trans = m_CanvasRoot.transform as RectTransform;

        return trans.sizeDelta;
    }

}
