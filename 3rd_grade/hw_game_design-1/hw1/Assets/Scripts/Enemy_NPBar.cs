using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Enemy_NPBar : MonoBehaviour
{
    public Slider e_NpBar;
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
        e_NpBar.value = val;
    }
}