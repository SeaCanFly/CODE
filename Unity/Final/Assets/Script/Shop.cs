using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Shop : MonoBehaviour {

    public Text cur_money;
    public Text warning;
	// Use this for initialization
	void Start () {
        cur_money.text = "Wallet:" + Manager.cur_user.money;
	}
    public void BuyStep()
    {
        if(Manager.cur_user.money<100)
        {
            warning.text = "Not Enough money!";
        }
        else
        {
            Manager.cur_user.money -= 100;
            Manager.cur_user.step++;
           Manager.SaveData();
            warning.text = "-100";
            cur_money.text = "Wallet:" + Manager.cur_user.money;
            
        }
    }
    public void BuyDelnode()
    {
        if (Manager.cur_user.money < 10)
        {
            warning.text = "Not Enough money!";
        }
        else
        {
            Manager.cur_user.money -= 10;
            Manager.cur_user.delnode++;
            Manager.SaveData();
            warning.text = "-10";
            cur_money.text = "Wallet:" + Manager.cur_user.money;

        }
    }
    public void BuyBoom()
    {
        if (Manager.cur_user.money < 200)
        {
            warning.text = "Not Enough money!";
        }
        else
        {
            Manager.cur_user.money -= 200;
            Manager.cur_user.boom++;
           Manager.SaveData();
            warning.text = "-200";
            cur_money.text = "Wallet:" + Manager.cur_user.money;

        }
    }
    public void BuyBoost()
    {
        if (Manager.cur_user.money < 300)
        {
            warning.text = "Not Enough money!";
        }
        else
        {
            Manager.cur_user.money -= 300;
            Manager.cur_user.boost++;
            Manager.SaveData();
            warning.text = "-300";
            cur_money.text = "Wallet:" + Manager.cur_user.money;

        }
    }
    public void CloseShop()
    {
        //Manager.SaveData();
        Manager.ui_manager.ClosePanel("shop");
    }
}
