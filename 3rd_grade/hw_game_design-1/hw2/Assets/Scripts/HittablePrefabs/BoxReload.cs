using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BoxReload : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnDestroy()
    {
        // dont have to reload for a period
        GameObject.Find("GameManager").GetComponent<GameManager>().SetFreeReload();
    }
}
