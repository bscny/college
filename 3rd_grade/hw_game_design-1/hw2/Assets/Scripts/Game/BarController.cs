using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BarController : MonoBehaviour
{
    [SerializeField]
    private Slider _slider;
    // Start is called before the first frame update
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {

    }

    public void SetVal(float val)
    {
        _slider.value = val;
    }

    public void Init(float maxVal, float initVal)
    {
        _slider.maxValue = maxVal;
        _slider.value = initVal;
    }
}
