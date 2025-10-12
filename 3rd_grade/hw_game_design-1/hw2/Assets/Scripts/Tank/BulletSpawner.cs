using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BulletSpawner : MonoBehaviour
{
    [SerializeField]
    private GameObject BulletPrefab;
    [SerializeField]
    private Transform TankCannon;
    [SerializeField]
    private float IntervalShooting;

    private float INTERVAL_SHOOTING;

    private float time;
    // Start is called before the first frame update
    void Start()
    {
        time = IntervalShooting;
        INTERVAL_SHOOTING = IntervalShooting;
    }

    // Update is called once per frame
    void Update()
    {
        time += Time.deltaTime;
        if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            if (time >= IntervalShooting)
            {
                GameObject bullet = Instantiate(BulletPrefab, this.transform.position, this.transform.rotation);
                bullet.transform.up = TankCannon.forward;
                
                time = 0;
            }

        }
    }

    // public func for game manager
    public void SwitchFireRate()
    {
        if(IntervalShooting == INTERVAL_SHOOTING)
        {
            IntervalShooting = 0;
        }
        else
        {
            IntervalShooting = INTERVAL_SHOOTING;
        }
    }
}
