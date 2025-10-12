using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Enemy_HPBar : MonoBehaviour
{
    public Slider e_HpBar;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void Set_HP(float val)
    {
        e_HpBar.value = val;
    }
}
