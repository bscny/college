using System.Collections;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using UnityEngine;

public class EnemySpawner : MonoBehaviour
{
    [SerializeField]
    private float spawnRatio = 0.3f;
    [SerializeField]
    private float IntervalSpawnEnemy;
    [SerializeField]
    private Transform FrontWall;
    [SerializeField]
    private GameObject TurretPrefab;
    [SerializeField]
    private GameObject CannonPrefab;

    private float availInnerRadius;
    private float availOuterRadius;

    private float timer;

    private int enemyNum;
    // Start is called before the first frame update
    void Start()
    {
        availInnerRadius = FrontWall.position.z - 10;
        availOuterRadius = FrontWall.position.z - 2;

        timer = IntervalSpawnEnemy - Time.deltaTime * 10;

        enemyNum = 0;
    }

    // Update is called once per frame
    void Update()
    {
        if(enemyNum < 10)
        {
            IntervalSpawnEnemy = 2;
        }
        else if(enemyNum < 20)
        {
            IntervalSpawnEnemy = 8;
        }
        else
        {
            IntervalSpawnEnemy = 10;
        }

        timer += Time.deltaTime;
        if (timer >= IntervalSpawnEnemy)
        {
            GenFrontWallEnemy();
            GenBackWallEnemy();
            GenRightWallEnemy();
            GenleftWallEnemy();

            timer = 0;
            enemyNum += 4;
        }
    }

    private void GenFrontWallEnemy()
    {
        Vector3 spawnPoint = new Vector3(Random.Range(-availOuterRadius, availOuterRadius), 0, Random.Range(availInnerRadius, availOuterRadius));

        CreatEnemy(spawnPoint);
    }

    private void GenBackWallEnemy()
    {
        Vector3 spawnPoint = new Vector3(Random.Range(-availOuterRadius, availOuterRadius), 0, Random.Range(-availOuterRadius, -availInnerRadius));

        CreatEnemy(spawnPoint);
    }

    private void GenRightWallEnemy()
    {
        Vector3 spawnPoint = new Vector3(Random.Range(availInnerRadius, availOuterRadius), 0, Random.Range(-availOuterRadius, availOuterRadius));

        CreatEnemy(spawnPoint);
    }

    private void GenleftWallEnemy()
    {
        Vector3 spawnPoint = new Vector3(Random.Range(-availOuterRadius, -availInnerRadius), 0, Random.Range(-availOuterRadius, availOuterRadius));

        CreatEnemy(spawnPoint);
    }

    private void CreatEnemy(Vector3 spawnPoint) 
    {
        float val = Random.Range(-1f, 1f);

        if(val > -spawnRatio)
        {
            Instantiate(TurretPrefab, spawnPoint, transform.rotation);
        }
        else
        {
            Instantiate(CannonPrefab, spawnPoint, transform.rotation);
        }
    }

    // public func for tank buller controller
    public void DecreaseEnemyNum()
    {
        enemyNum--;
    }
}
