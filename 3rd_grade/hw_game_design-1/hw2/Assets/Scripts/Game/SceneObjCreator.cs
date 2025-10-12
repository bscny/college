using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SceneObjCreator : MonoBehaviour
{
    [SerializeField]
    private float IntervalSpawnBox;
    [SerializeField]
    private Transform FrontWall;
    [SerializeField]
    private GameObject[] BoxPrefab;

    private float halfLength;

    private float offsetBox;

    private float timer;

    // Start is called before the first frame update
    void Start()
    {
        offsetBox = BoxPrefab[0].transform.localScale.x;
        halfLength = FrontWall.position.z - offsetBox;
        timer = 0;

        GenFrontWallObj();
        GenBackWallObj();
        GenRightWallObj();
        GenleftWallObj();
    }

    // Update is called once per frame
    void Update()
    {
        timer += Time.deltaTime;
        if(timer >= IntervalSpawnBox)
        {
            GenFrontWallObj();
            GenBackWallObj();
            GenRightWallObj();
            GenleftWallObj();

            timer = 0;
        }
    }

    private void GenFrontWallObj()
    {
        Vector3 spawnPoint = new Vector3(Random.Range(-halfLength, halfLength), Random.Range(halfLength / 3, halfLength), halfLength + offsetBox / 2);

        CreateBox(spawnPoint);
    }

    private void GenBackWallObj()
    {
        Vector3 spawnPoint = new Vector3(Random.Range(-halfLength, halfLength), Random.Range(halfLength / 3, halfLength), -(halfLength + offsetBox / 2));

        CreateBox(spawnPoint);
    }

    private void GenRightWallObj()
    {
        Vector3 spawnPoint = new Vector3(halfLength + offsetBox / 2, Random.Range(halfLength / 3, halfLength), Random.Range(-halfLength, halfLength));

        CreateBox(spawnPoint);
    }

    private void GenleftWallObj()
    {
        Vector3 spawnPoint = new Vector3(-(halfLength + offsetBox / 2), Random.Range(halfLength / 3, halfLength), Random.Range(-halfLength, halfLength));

        CreateBox(spawnPoint);
    }

    private void CreateBox(Vector3 spawnPoint)
    {
        Instantiate(BoxPrefab[Random.Range(0, BoxPrefab.Length)], spawnPoint, transform.rotation);
    }
}
