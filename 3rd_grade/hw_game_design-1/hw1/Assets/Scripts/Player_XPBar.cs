using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Player_XPBar : MonoBehaviour
{
    public Slider p_XpBar;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void Set_XP(float val)
    {
        p_XpBar.value = val;
    }
}
