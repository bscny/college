using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sword_empty : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        this.transform.position = GameObject.Find("StickerMan").GetComponent<StickerMan>().Get_Pos();

        float d_x = GameObject.Find("StickerMan").GetComponent<StickerMan>().Get_dir_X();
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

        if (d_x * this.transform.localScale.x < 0)   //  switch side
        {
            this.transform.localScale = new Vector3(-1 * this.transform.localScale.x, this.transform.localScale.y, this.transform.localScale.z);
        }
    }

}
