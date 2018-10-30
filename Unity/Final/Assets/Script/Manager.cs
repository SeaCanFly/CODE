using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.SceneManagement;
public class Manager : MonoBehaviour {

    // Use this for initialization
    static Manager instance;
    public static UIManager ui_manager;
    public static UserClass cur_user;
    public static int cur_score;
    [HideInInspector]
    public static string cur_path;
    void Awake()
    {
        if (instance == null)
        {
            instance = this;
            DontDestroyOnLoad(this);
            cur_user = new UserClass();
            ui_manager = new UIManager();
            name = "Manager";
        }
        else if (this != instance)
        { 
            Destroy(gameObject);
        }
    }
    public static bool SaveData()
    {
        try
        {
            string contents = JsonUtility.ToJson(cur_user, true);
            File.WriteAllText(cur_path, contents);
        }
        catch (System.Exception ex)
        {
            Debug.Log(ex.Message);
            return false;
        }
        return true;
    }
  
}


