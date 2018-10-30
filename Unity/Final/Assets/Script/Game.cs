using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Game : MonoBehaviour {
    public GameObject[] cube;
    public Text number;
    public Text show;
    public Text score;
    public Text boom_number;
    public Text delnode_number;
    public Text boost_number;
    public Text step_number;
    public Text add_money_text;
    const int max_row = 6;
    const int max_col = 9;
    int[] creat_arry = { max_row, max_row, max_row, max_row, max_row, max_row, max_row,max_row,max_row};
    
    CubeManager[,] list = new CubeManager[max_row, max_col];
    Buffer[] stack = new Buffer[max_col*max_row/3];
    Buffer[] del_buffer = new Buffer[max_col*max_row/3];
    Buffer create_buffer = new Buffer();
    int x1, y1,x2,y2;
    public bool init_state = false;
    bool check_state = false;
    bool ok = true;
    bool work_start = false;
    int boom = 0;
    public bool boom_state = false;
    int del = 0;
    public bool delnode_state = false;
    int boost = 0;
    public bool boost_state = false;
    int add_step_count = 0;

    int s = 0;
    int final_score = 0;
    int step = 10;
    int w = 0;
    GameObject select_temp;
    Sprite spriteA;
    Sprite spriteB;
    Sprite spriteC;
    Sprite spriteBoom;
    Sprite spriteDel;
    Sprite spriteBoost;
    Sprite t;

    // Use this for initialization
    bool NodeCheck(int i,int j)
    {
        
        int tempj_right = j + 1;
        int tempj_left = j - 1;
        int tempi_up = i + 1;
        int tempi_down = i - 1;
        int countj = 0;
        int countj_right = 1;
        int countj_left = 1;
        int counti = 0;
        int counti_up = 1;
        int counti_down = 1;
        bool t = false;
        while (tempj_right < max_col)
        {
            if (list[i, tempj_right].cube_object!=null&&list[i, j].cube_object.GetComponent<Cube>().type == list[i, tempj_right].cube_object.GetComponent<Cube>().type)
            {
                tempj_right++;
                countj_right++;
            }
            else
            {
                break;
            }
        }
        while (tempj_left >= 0)
        {
            if (list[i, tempj_left].cube_object != null && list[i, j].cube_object.GetComponent<Cube>().type == list[i, tempj_left].cube_object.GetComponent<Cube>().type)
            {
                tempj_left--;
                countj_left++;
            }
            else
            {
                break;
            }
        }
        countj = countj_left + countj_right - 1;
        while (tempi_up < max_row)
        {
            if (list[tempi_up, j].cube_object != null && list[i, j].cube_object.GetComponent<Cube>().type == list[tempi_up, j].cube_object.GetComponent<Cube>().type)
            {
                tempi_up++;
                counti_up++;
            }
            else
            {
                break;
            }
        }
        while (tempi_down >= 0)
        {
            if (list[tempi_down, j].cube_object != null && list[i, j].cube_object.GetComponent<Cube>().type == list[tempi_down, j].cube_object.GetComponent<Cube>().type)
            {
                tempi_down--;
                counti_down++;
            }
            else
            {
                break;
            }
        }
        counti = counti_up + counti_down - 1;
        if (counti >= 3)
        {
            if (list[i, j].cube_object.GetComponent<Cube>().flag != -1)
            {
                list[i, j].cube_object.GetComponent<Cube>().flag = -1;
            
                stack[s].push(list[i, j]);
                t = true;
            }
            for (int temp = 1; temp < counti_up; temp++)
            {
                if (list[i + temp, j].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[i + temp, j].cube_object.GetComponent<Cube>().flag = -1;
                    
                    stack[s].push(list[i + temp, j]);
                    t = true;
                }
            }
            for (int temp = 1; temp < counti_down; temp++)
            {
                if (list[i - temp, j].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[i - temp, j].cube_object.GetComponent<Cube>().flag = -1;
                  
                    stack[s].push(list[i - temp, j]);
                    t = true;
                }
            }
        }
        if (countj >= 3)
        {
            if (list[i, j].cube_object.GetComponent<Cube>().flag != -1)
            {
                list[i, j].cube_object.GetComponent<Cube>().flag = -1;
              
                stack[s].push(list[i, j]);
                t = true;
            }
            for (int temp = 1; temp < countj_right; temp++)
            {
                if (list[i, j + temp].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[i, j + temp].cube_object.GetComponent<Cube>().flag = -1;
                
                    stack[s].push(list[i, j + temp]);
                    t = true;
                }
            }
            for (int temp = 1; temp < countj_left; temp++)
            {
                if (list[i, j - temp].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[i, j - temp].cube_object.GetComponent<Cube>().flag = -1;
                 
                    stack[s].push(list[i, j - temp]);
                    t = true;
                }
            }
        }
            if (t == true)
            {
                s++;
                ok = false;
                return ok;
            }
         return true;
     }
       
    
    bool Check()
    {
        ok = true; 
        for(int i=0;i<max_row;i++)
        {
           
            for(int j=0; j<max_col;j++)
            {
                NodeCheck(i, j); 
            }
        }
        return ok;
    }
    bool CheckCreate()
    {

        ok = true;
        while(create_buffer.top!=-1)
        {
            CubeManager t = create_buffer.Pop();
            if(t.cube_object.GetComponent<Cube>().flag!=-1)
            NodeCheck(t.x, t.y);
        }
        return ok;
    }
    void DelNode(int i,int j)
    {
        
        if (list[i, j].cube_object!=null)
        {
            if (list[i, j].cube_object.GetComponent<Cube>().flag == -1)
            {
                
                Destroy(list[i, j].cube_object,0.1f);
                list[i, j].cube_object = null;//
                list[i, j].state = false;
               

                creat_arry[j]++;
            }
        }
    }
    bool Correct()
    {
        for(int j=0;j<max_col;j++)
        {
            if (creat_arry[j] == 0) continue;
            for(int i=0;i<max_row;i++)
            {
                
                if(list[i,j].state==true)
                {
                    continue;
                }
                else
                {
                    int pos = i;
                    i++;
                    while(i<max_row)
                    {
                        if(list[i,j].state==true)
                        {
                            list[pos, j].Swap(list[i, j]);
                            create_buffer.push(list[pos, j]);
                            pos++;
                            i++;
                        }
                        else
                        {
                            i++;
                        }
                    }
                }
            }
        }
        return true;
    }
    bool KillCubes()
    {
        int num = 0;
        while (num <=s-1)
        {
            if (stack[num].top != -1)
            {
                if(boom_state)
                {
                    t = spriteBoom;
                    w = 1;
                    boom_state = false;
                }
                else if(delnode_state)
                {
                    t = spriteDel;
                    w = 1;
                    delnode_state = false;
                }
                else if(boost_state)
                {
                    t = spriteBoost;
                    w = 1;
                    boost_state = false;
                }

                else if (stack[num].top >= 4)
                {
                    Manager.cur_user.money += 10;
                    add_money_text.text = "[Current Money:" + Manager.cur_user.money + "]";
                    t = spriteB;
                    w = 3;
                }
                else if (stack[num].top == 3)
                {
                    t = spriteC;
                    w = 2;
                }
                else if (stack[num].top <= 2)
                {
                    t = spriteA;
                    w = 1;
                }
            }
            while (stack[num].top != -1)
            {
                
               
                CubeManager del_temp = stack[num].Pop();
                list[del_temp.x, del_temp.y].cube_object.GetComponent<SpriteRenderer>().sprite = t;
                if (del_temp != null)
                {
                    DelNode(del_temp.x, del_temp.y);
                    if (work_start)
                    {
                        final_score += w;
                        score.text = final_score.ToString();
                        Manager.cur_score = final_score;
                    }
                }
            }
            num++;
        }
        s = 0;
        return true;
    }
   
    IEnumerator Init()
    {
        for (int i = 0; i < max_row; i++)
        {
            for (int j = 0; j < max_col; j++)
            { 
                
                if(creat_arry[j] > 0)
                {
                    int posx = max_row - creat_arry[j];
                    int type = Random.Range(0, 4);
                    Vector3 position = new Vector3(-0.084f + j * (1.034f), 1.66f);
                    list[posx,j]= new CubeManager(type,posx,j,Instantiate(cube[type], position, new Quaternion(0.0f, 0.0f, 0.0f, 1.0f)));                
                    creat_arry[j]--;
                }
            }
           yield return new WaitForSeconds(0.5f);
        }
        if (Check() == false)
        {
            KillCubes();
            Correct();
            StartCoroutine(Create());
        }
        init_state = true;
    }
    IEnumerator Create()
    {
        for (int j = 0; j < max_col; j++)
        {
            if (creat_arry[j] == 0) continue;
            while(creat_arry[j]>0)
            {
                int posx = max_row - creat_arry[j];
                int type = Random.Range(0, 4);
                Vector3 position = new Vector3(-0.084f + j * (1.034f), 1.66f);
                list[posx, j] = new CubeManager(type, posx, j, Instantiate(cube[type], position, new Quaternion(0.0f, 0.0f, 0.0f, 1.0f)));
                creat_arry[j]--;
                create_buffer.push(list[posx, j]);
                yield return new WaitForSeconds(0.1f);
            }
        }
        check_state = true;
    }
    private void Awake()
    {
        init_state = false;
        StartCoroutine(Init());
    }
    void Start()
    {
        for (int i = 0; i < max_row * max_col / 3; i++)
        {
            stack[i] = new Buffer();
            del_buffer[i] = new Buffer();
        }
        create_buffer = new Buffer();
        x1 = -1000;
        x2 = -1000;
        y1 = -1000;
        y2 = -1000;
        add_step_count = Manager.cur_user.step;
        boost = Manager.cur_user.boost;
        boom = Manager.cur_user.boom;
        del = Manager.cur_user.delnode;
        add_money_text.text = "[Current Money:" + Manager.cur_user.money + "]";
        number.text = step.ToString();
        boom_number.text = boom.ToString();
        delnode_number.text = del.ToString();
        boost_number.text = boost.ToString();
        step_number.text = add_step_count.ToString();
        spriteA = Resouce.ResourcesLoadCheckNull<Sprite>("8");
        spriteB = Resouce.ResourcesLoadCheckNull<Sprite>("9");
        spriteC = Resouce.ResourcesLoadCheckNull<Sprite>("10");
        spriteBoom = Resouce.ResourcesLoadCheckNull<Sprite>("11");
        spriteDel = Resouce.ResourcesLoadCheckNull<Sprite>("12");
        spriteBoost = Resouce.ResourcesLoadCheckNull<Sprite>("13");

    }
  void SwapCube()
    {
        GameObject temp = list[x1, y1].cube_object;
        list[x1, y1].cube_object = list[x2, y2].cube_object;
        list[x2, y2].cube_object = temp;
        list[x1, y1].cube_object.GetComponent<Cube>().SetPositon(list[x1, y1].x, list[x1, y1].y);
        list[x2, y2].cube_object.GetComponent<Cube>().SetPositon(list[x2, y2].x, list[x2, y2].y);
        Vector3 pos = list[x1, y1].cube_object.transform.position;
        list[x1, y1].cube_object.transform.position = list[x2, y2].cube_object.transform.position;
        list[x2, y2].cube_object.transform.position = pos;
    }
    void Clean()
    {
        for (int i = 0; i < max_row; i++)
        {
            for (int j = 0; j < max_col; j++)
            {
                if(list[i,j].cube_object)
                {
                    Destroy(list[i, j].cube_object);
                }
              
            }
        }
        for(int i=0;i<max_col;i++)
        {
            creat_arry[i] = max_row;
        }
    }
    bool Work()
    {
        work_start = true;
        if (step == 0)
        {
            init_state = false;
            show.text = "Finish";
            if (final_score < 104)
            {
                Manager.cur_user.step = add_step_count;
                Manager.cur_user.delnode = del;
                Manager.cur_user.boom = boom;
                Manager.cur_user.boost = boost;
                Manager.SaveData();
                Manager.ui_manager.ShowPanel("lose");
            }
            else if (final_score >= 104 && final_score < 190)
            {
                Manager.cur_user.step = add_step_count;
                Manager.cur_user.delnode = del;
                Manager.cur_user.boom = boom;
                Manager.cur_user.boost = boost;
                Manager.SaveData();
                Manager.ui_manager.ShowPanel("win1");
            }
            else if (final_score >= 190 && final_score < 290)
            {
                Manager.cur_user.step = add_step_count;
                Manager.cur_user.delnode = del;
                Manager.cur_user.boom = boom;
                Manager.cur_user.boost = boost;
                Manager.SaveData();
                Manager.ui_manager.ShowPanel("win2");
            }
            else if (final_score >= 290)
            {
                Manager.cur_user.step = add_step_count;
                Manager.cur_user.delnode = del;
                Manager.cur_user.boom = boom;
                Manager.cur_user.boost = boost;
                Manager.SaveData();
                Manager.ui_manager.ShowPanel("win3");
            }
        }
        Collider2D[] col = Physics2D.OverlapPointAll(Camera.main.ScreenToWorldPoint(Input.mousePosition));
        if (col.Length > 0)
        {
            foreach (Collider2D c in col)
            {

                if (c.tag == "node")
                {
                    if (Input.GetMouseButtonDown(0))
                    {
                        x1 = c.gameObject.GetComponent<Cube>().x;
                        y1 = c.gameObject.GetComponent<Cube>().y;

                    }
                    if (Input.GetMouseButtonDown(1))
                    {
                        x2 = c.gameObject.GetComponent<Cube>().x;

                        y2 = c.gameObject.GetComponent<Cube>().y;
                    }
                 
                }
                if (c.tag=="boom")
                {
                    if (Input.GetMouseButtonDown(0))
                    {
                        boom_state = true;
                        delnode_state = false;
                        boost_state = false;
                    }
                    x1 = -1000;
                     y1 = -1000;
                     x2 = -1000;
                     y2 = -1000;
                     return false;
                }
                else if(c.tag=="delnode")
                {
                    if (Input.GetMouseButtonDown(0))
                    {
                        delnode_state = true;
                        boost_state = false;
                        boom_state = false;
                    }
                    x1 = -1000;
                    y1 = -1000;
                    x2 = -1000;
                    y2 = -1000;
                    return false;
                }
                else if(c.tag=="boost")
                {
                    if (Input.GetMouseButtonDown(0))
                    {
                        boost_state = true;
                        delnode_state = false;
                        boom_state = false;
                    }
                    x1 = -1000;
                    y1 = -1000;
                    x2 = -1000;
                    y2 = -1000;
                    return false;
                }
                else if(c.tag=="step")
                {
                    if (Input.GetMouseButtonDown(0))
                    {
                        if (add_step_count > 0)
                        {
                            step++;
                            add_step_count--;
                            step_number.text = add_step_count.ToString();
                            number.text = step.ToString();
                        }
                        x1 = -1000;
                        y1 = -1000;
                        x2 = -1000;
                        y2 = -1000;
                    }
                    return false;
                }
            }
        }
        if(boom_state)
        {
            if (x1 == -1000 || y1 == -1000)
                return false;
            if (list[x1, y1].cube_object == null)
                return false;
            if (boom>0)
            {
        
                if(list[x1,y1].cube_object.GetComponent<Cube>().flag!=-1)
                {
                    list[x1, y1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1, y1]);
                }
                if (x1+1<max_row&&list[x1+1, y1].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[x1+1, y1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1+1, y1]);
                }
                if (x1-1>=0&&list[x1-1, y1].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[x1-1, y1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1-1, y1]);
                }
                if (y1+1<max_col&&list[x1, y1+1].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[x1, y1+1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1, y1+1]);
                }
                if (y1-1>=0&&list[x1, y1 - 1].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[x1, y1 - 1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1, y1 - 1]);
                }
                if (y1+1<max_col&&list[x1+1, y1+1].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[x1+1, y1+1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1+1, y1+1]);
                }
                if (x1+1<max_row&&y1-1>=0&&list[x1+1, y1-1].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[x1+1, y1-1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1+1, y1-1]);
                }
                if (x1-1>=0&&y1-1>=0&&list[x1-1, y1-1].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[x1-1, y1-1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1-1, y1-1]);
                }
                if (x1-1>=0&&y1+1<max_col&&list[x1-1, y1+1].cube_object.GetComponent<Cube>().flag != -1)
                {
                    list[x1-1, y1+1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1-1, y1+1]);
                }

                s++;
                boom--;
                boom_number.text = boom.ToString();
            }
            x1 = -1000;
            y1 = -1000;
            x2 = -1000;
            y2 = -1000;
            return true;
        }
        else if(delnode_state)
        {
            if(x1==-1000 || y1==-1000)
                return false;
            if (list[x1, y1].cube_object == null)
                return false;
            if (del>0)
            {
                if(list[x1,y1].cube_object.GetComponent<Cube>().flag!=-1)
                {
                    list[x1, y1].cube_object.GetComponent<Cube>().flag = -1;
                    stack[s].push(list[x1, y1]);

                }
                s++;
                del--;
                delnode_number.text = del.ToString();
            }
            x1 = -1000;
            y1 = -1000;
            x2 = -1000;
            y2 = -1000;
            return true;
        }
        else if(boost_state)
        {
            if (x1 == -1000 || y1 == -1000)
                return false;
            if (list[x1, y1].cube_object == null)
                return false;
            if (boost>0)
            {
                int t = list[x1, y1].cube_object.GetComponent<Cube>().type;
                for (int i = 0; i < max_row; i++)
                {
                    for (int j = 0; j < max_col; j++)
                    {
                        if (list[i, j].cube_object.GetComponent<Cube>().type == t)
                        {
                            if (list[i, j].cube_object.GetComponent<Cube>().flag != -1)
                            {
                                list[i, j].cube_object.GetComponent<Cube>().flag = -1;
                                stack[s].push(list[i, j]);
                            }

                        }

                    }
                }
                s++;
                boost--;
                boost_number.text = boost.ToString();
            }
            x1 = -1000;
            y1 = -1000;
            x2 = -1000;
            y2 = -1000;
            return true;
        }
        else if (x1 != -1000 && x2 != -1000 && y1 != -1000 && y2 != -1000)
        {
            if (x2 - x1 > 1 || x2 - x1 < -1 || y2 - y1 > 1 || y2 - y1 < -1)
            { 
                x1 = -1000;
                x2 = -1000;
                y1 = -1000;
                y2 = -1000;
                return false;
            }
            else
            {
                SwapCube();
                bool nc1 = NodeCheck(x1, y1);
                bool nc2 = NodeCheck(x2, y2);
                if (nc1==true&&nc2==true)
                {
                    SwapCube();        
                    x1 = -1000; x2 = -1000; y1 = -1000; y2 = -1000;
                    return false;
                }
                x1 = -1000; x2 = -1000; y1 = -1000; y2 = -1000;
                step--;
                number.text = step.ToString();
              
                return true;
            }
        }
        return false;
    }
    void Update()
    {
        if (init_state == true)
        {
            show.text = "Wait";
            if (check_state == true)
            {

                if (CheckCreate() == false)
                {
                    check_state = false;
                    KillCubes();
                    Correct();    
                    StartCoroutine(Create());
                }
                else
                {
                    show.text = "START";
                    if(Work()==true)
                    {
                        check_state = false;
                        KillCubes();
                        Correct();                
                        StartCoroutine(Create());
                    }
                }
            }
        }
    }   
}
