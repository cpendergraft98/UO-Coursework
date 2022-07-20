using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class SlimeAI_v2 : MonoBehaviour
{
    UnityEngine.AI.NavMeshAgent agent;
    GameObject player;
    Scene currScene;

    private float obstacleRange = 3.0f;
    private float changeDirectionTimer = 1.2f;
    private float timer = 0.0f;

    // Values to compare against player distance to determine the
    // state the agent should be in
    private string sceneName;
    public float ChaseDist = 15.0f; // Distance at which agent chases Player
    public float WanderMax = 45.0f; // Max Dist from player where the enemy will still wander

    // States
    private bool _rest;
    private bool _chase;
    private bool _wander;
  
    // Animator
    private Animator _animator;

    void Start()
    {
      agent = GetComponent<UnityEngine.AI.NavMeshAgent>();
      player = GameObject.FindGameObjectWithTag("Player");
      currScene = SceneManager.GetActiveScene();
      sceneName = currScene.name;
    
      // Set Animator
      _animator = GetComponent<Animator>();

      // Set States
      _rest = true;
      _chase = false;
      _wander = false;
    }

    void Update()
    {
        var distToPlayer = Vector3.Distance(player.transform.position, this.transform.position);
        // if in rest state
        if(_rest)
        {
            // if in wandering range:
            if ((distToPlayer < WanderMax) && (distToPlayer > ChaseDist))
            {
                _rest = false;
                _chase = false;
                _wander = true;
            }
            // if in chasing range:
            else if (distToPlayer <= ChaseDist) 
            {
                _rest = false;
                _wander = false;
                _chase = false;
            }
            else { }
        }

        // if in wander state
        if(_wander)
        {
            // if the player is to far away enter rest state
            if (distToPlayer >= WanderMax)
            {
                _wander = false;
                _chase = false;
                _rest = true;
            }
            // if the player has entered chasing range
            else if (distToPlayer <= ChaseDist)
            {
                _rest = false;
                _wander = false;
                _chase = true;
            }
            else if (sceneName == "level3 Cliffs")
            {
                UnityEngine.AI.NavMeshHit hit1;
                if (UnityEngine.AI.NavMesh.FindClosestEdge(transform.position, out hit1, UnityEngine.AI.NavMesh.AllAreas))
                {
                    if (hit1.distance < 0.5f)
                    {
                        float angle = Random.Range(155, 200);
                        transform.Rotate(0, angle, 0);
                        timer = changeDirectionTimer;
                    }
                }
            }
            else
            {
                wander();
            }
        }

        // if in chase state
        if(_chase)
        {
            // if the player has escaped return to wander
            if((distToPlayer >= ChaseDist) && (distToPlayer <= WanderMax))
            {
                _rest = false;
                _chase = false;
                _wander = true;
            }
            // otherwise chase the player
            else
            {
                transform.LookAt(player.transform);
                agent.SetDestination(player.transform.position);
            }
        }

        // Set animator states
        _animator.SetBool("_chase", _chase);
        _animator.SetBool("_wander", _wander);
    }

    void wander()
    {
        transform.Translate(0, 0, agent.speed * Time.deltaTime);
        var dist = Vector3.Distance(player.transform.position, transform.position);
        Ray lookAhead = new Ray(transform.position, transform.forward);
        RaycastHit hit;
        if (Physics.SphereCast(lookAhead, 0.75f, out hit))
        {
            if (hit.distance < obstacleRange)
            {
                float angle = Random.Range(-90, 90);
                transform.Rotate(0, angle, 0);
            }
            timer = changeDirectionTimer;
        }
        else
        {
            timer -= Time.deltaTime;
            if (timer > 0)
                return;
            else
            {
                float angle = Random.Range(-110, 110);
                transform.Rotate(0, angle, 0);
            }
        }
    }
}
