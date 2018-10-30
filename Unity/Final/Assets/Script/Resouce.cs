using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;

public class Resouce : MonoBehaviour {
    public static GameObject InstantiateGameObject(GameObject parent, GameObject prefab)
    {

        GameObject go = GameObject.Instantiate(prefab) as GameObject;

        if (go != null && parent != null)
        {
            Transform t = go.transform;
            t.SetParent(parent.transform);
            t.localPosition = Vector3.zero;
            t.localRotation = Quaternion.identity;
            t.localScale = Vector3.one;

            RectTransform rect = go.transform as RectTransform;
            if (rect != null)
            {
                rect.anchoredPosition = Vector3.zero;
                rect.localRotation = Quaternion.identity;
                rect.localScale = Vector3.one;
                if (rect.anchorMin.x != rect.anchorMax.x && rect.anchorMin.y != rect.anchorMax.y)
                {
                    rect.offsetMin = Vector2.zero;
                    rect.offsetMax = Vector2.zero;
                }
            }

            go.layer = parent.layer;
        }
        return go;
    }
    public static T ResourcesLoadCheckNull<T>(string name) where T : UnityEngine.Object
    {
        T loadGo = Resources.Load<T>(name);

        if (loadGo == null)
        {
            Debug.Log("Resources.Load [ " + name + " ] is Null !!");
            return default(T);
        }

        return loadGo;
    }

    public static Sprite ResourcesLoadSprite(string name)
    {
        return ResourcesLoadCheckNull<Sprite>("Sprites/" + name);
    }


    public static void LoadFile(string path)
    {
        string strTemp;
        TextAsset data = null;
        TextReader reader = null;

        data = Resources.Load(path, typeof(TextAsset)) as TextAsset;

        if (data != null)
            reader = new StringReader(data.text);

        if (reader != null)
        {
            while ((strTemp = reader.ReadLine()) != null)
            {
                Debug.Log(strTemp);
            }

            reader.Close();
        }
    }
}
