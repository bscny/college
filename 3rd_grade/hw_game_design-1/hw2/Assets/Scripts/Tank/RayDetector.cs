using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RayDetector : MonoBehaviour
{
    [SerializeField]
    private GameObject RayIndicatorOn;
    [SerializeField] 
    private GameObject RayIndicatorOff;
    [SerializeField]
    private LayerMask LayerToDetect;

    Ray ray;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        ray = new Ray(transform.position, transform.forward);

        if(Physics.Raycast(ray, out RaycastHit hit, 999f, LayerToDetect))
        {
            if(hit.collider.gameObject.tag != "Enemy")
            {
                RayIndicatorOn.SetActive(false);
                RayIndicatorOff.SetActive(true);
            }
            else
            {
                RayIndicatorOn.SetActive(true);
                RayIndicatorOff.SetActive(false);
            }

            RayIndicatorOn.transform.position = hit.point;
            RayIndicatorOff.transform.position = hit.point;
        }
    }
}
