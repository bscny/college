using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class Cannon : MonoBehaviour
{
    private Transform Tank;

    private Vector3 dir;
    // Start is called before the first frame update
    void Start()
    {
        Tank = GameObject.Find("Tank").transform;

        TrackTank();
    }

    // Update is called once per frame
    void Update()
    {
        TrackTank();
    }

    private void TrackTank()
    {
        dir = new Vector3(Tank.position.x - transform.position.x, 0, Tank.position.z - transform.position.z);
        dir = dir.normalized;

        transform.forward = dir;
    }

    private void OnDestroy()
    {
        GameObject.Find("GameManager").GetComponent<GameManager>().KillEnemy();
    }

}
