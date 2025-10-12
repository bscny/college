using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy_sword : MonoBehaviour
{
    public int np_full = 5000;
    public float size_up = 2f;

    float d_x;

    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void FixedUpdate()
    {
        // about how the sword rotate while moving
        if (GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().Get_isOnGround() == true)
        {
            this.transform.rotation = Quaternion.Euler(0, 0, 0);
        }
        else
        {
            d_x = GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().Get_dir_X();
            if (d_x > 0)
            {
                d_x = 1;
            }
            else if (d_x < 0)
            {
                d_x = -1;
            }
            else
            {
                d_x = 0;
            }

            if (GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().Get_Velocity() > 0)
            {
                this.transform.rotation = Quaternion.Euler(0, 0, d_x * 45);
            }
            else if (GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().Get_Velocity() < 0)
            {
                this.transform.rotation = Quaternion.Euler(0, 0, d_x * -45);
            }
            else if (GameObject.Find("StickerMan (enemy)").GetComponent<Enemy>().Get_Velocity() == 0)
            {
                this.transform.rotation = Quaternion.Euler(0, 0, d_x * 0);
            }
        }

    }
    public void lengthing()
    {
        this.transform.localScale = new Vector3(size_up * this.transform.localScale.x, this.transform.localScale.y, this.transform.localScale.z);
    }
    public void dislengthing()
    {
        this.transform.localScale = new Vector3(this.transform.localScale.x / size_up, this.transform.localScale.y, this.transform.localScale.z);
    }
}