using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Player_NPBar : MonoBehaviour
{
    public Slider p_NpBar;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void Set_NP(float val)
    {
        p_NpBar.value = val;
    }
}
