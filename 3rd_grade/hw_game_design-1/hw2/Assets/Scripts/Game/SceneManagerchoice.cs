using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SceneManagerChoice : MonoBehaviour
{
    public void GoMainScene()
    {
        SceneManager.LoadScene(1);
    }

    public void GoStartScene()
    {
        SceneManager.LoadScene(0);
    }
}
