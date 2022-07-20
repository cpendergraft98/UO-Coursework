/*
File Name: TPSAlogorithm.js

File purpose: This file contains the code for the TPS alogrithm, a distance
matrix is given to the Prim's Alogrithm as input, the algorithm then runs,
generating a list of all the edges in the MST.  Using that edge list we
generate a adjacency list for all the nodes in the MST, we then run a DFS on the
adjacency list, generating the optimal path, and finally we add the start node
back to the end of the DFS path.

Authours: Joseph Cates

How this fits into the larger system: This file contains all the code for the
TPS algorithm, so the system first genreates a distance matrix were all the
addresses the user has inputed represnet the nodes in the matrix.  We feed this
matrix to this file, and the output is a list were with the start node at the
head and the tail of the list, and the index in the list is the order to vist
the address, so the ith address will be the i+1 address to stop at(its the
i+1 address due to zero based indexing).  This output list is then used to
generate the final map with the markers denoting what order to vist all the
addresses.
*/

/* https://libraries.io/npm/priority-heap-queue/0.1.0
This libaray is for import is for Priority Queues.  As a group we decided
that it would be more responsible to use a standard Priority Queue library as
it would be more effeicent than any Priority Queue we could write. The
Priority Queue is used in prim's algorithm.
*/
var PriorityQueue = require('priority-heap-queue')

function dfs (edge) {

  /* The adjlist varaible is a list that will hold the adjlist that we are
  creating to run the DFS on */
  let adjlist = []

  /* this visted list holds what nodes we have and have not visted in the DFS,
  all the values are intilized to false at first, as we have not visted any
  nodes when DFS is first called */
  let visited = Array(edge.length).fill(false)

  /* this answer list will hold the output of the dfs, which will be a preorder
  path of the MST */
  let answer = []

  /* This for loop beings generating the adjaceny list, we first go through and
  append the second node in the edge pair to the adjaceny list of the first node
  in the edge list  */
  for (let i = 0; i < edge.length; i++) {
    if (edge[i][1] === null) {
      adjlist.push([])
    } else {
      adjlist.push([edge[i][1]])
    }
  }

  /* This for loop finishes generating the adjaceny list, we first go through and
  append the first node in the edge pair to the adjaceny list of the second node
  in the edge list  */
  for (let x = 1; x < edge.length; x++) {
    if (edge[x][1] === null) {
      adjlist[edge[x][0]].push(0)
      adjlist[0].push(x)
    } else {
      adjlist[edge[x][1]].push(edge[x][0])
    }
  }

  /* after creating the adjacency list, we then call the actually dfs algorithm
  with the index as zero, as we want to ensure that our preorder search starts
  with the starting address, we then pass the adjlist, visted, and answer lists
  to the algorithm. */
  dfsalgorithm(0, adjlist, visited, answer)

  /* after the dfsalgorithm returns the MST path we append the start node at the
  end of the path to meet the requirments of the TSP problem. We are able to due
  this and still ensure that our soultion is no more than twice the
   optimal cost, due to the triangle inequality.  The triangle inequality
   says that the sum of any two lengths of any two sides of a triangle, must
   be greater than or equal to the length of the remaining side.  This means
   that if we have a triangle made from three nodes, A, the start node,
   B, the last node in the MST path, and C, a node that is connected to both B
   and A.  Even if the edge weight from B to A is larger than the edge weight
   from C to A,  it is better to go to B to A, as the cost of going to B to C,
   then C to A will at best be equal to the cost of B to A.    */
  answer.push(0)


  /* we then return the output of the dfs */
  return answer
}

function dfsalgorithm (index, adjList, visited, answer) {
  /* This DFS algoritm is recursive, so we first update the node that we are
  currently work with to visted */
  visited[index] = true
  /* we then push the node that we are currently work on to the end of the
  output list */
  answer.push(index)

  /* This for loop goes through the adjaceny list of the node that we are
  currently working on,i, if we run into a node in the adjlist that we have not
  visted then we call DFS on that node, we pass the new dfsalgorithm algorithm
  call the index of the node that we have not visted,the same adjList,the visted
  node list so we can update the visted value of the new call, and the
  answer list so we can update it */
  for (let i = 0; i < adjList[index].length; i++) {
    if (visited[adjList[index][i]] === false) {
      dfsalgorithm(adjList[index][i], adjList, visited, answer)
    }
  }
}

function prim (matrix) {
  /* this key[u] holds the shortest distance from u to any vertex in our
  visted graph (The visted graph is the graph were visted[node] == true).
  At first it is intilized to the MAX_VALUE, as we do not know the shortest
  distance for any of the nodes in the graph (except the start node)  */
  let key = Array(matrix.length).fill(Number.MAX_VALUE)

 /* this visted list tracks if we have visted all the nodes that are connected
 to the node we are currently working with.  If this value is true then we have
 visted all the child nodes connected to that node, and updated all there values,
 ensuring that we have added the lightest edge that gets to us to that edge in
 the MST  */
  let visted = Array(matrix.length).fill(false)

  /* this pred list tracks the node that is already in the mst, that we used
  to reach this new node.  I.E pred[u], where u is a node in the graph, is the
  endpoint of the edge in the visted graph. This list is intilized to null
  as we do not know any of the pred of any nodes in the graph. */
  let pred = Array(matrix.length).fill(null)

  /* here we update the values for the root node, we know that the distance
  form the root node to the root node is zero, so that is what we set it too. */
  key[0] = 0
  pred[0] = null

  /* here we create a priority queue that tracks all the nodes we have not
  visted */
  let queue = new PriorityQueue({kind: 'min'});

  /* this for loop adds all the nodes into the priority queue */
  for (let i = 0; i < matrix.length; i++) {
    queue.insert(key[i], i)
  }

  /* this while loop is the meat of the Prims algorithm, we go stay in this loop
  untill the queue is empty, as when the queue is empty all the nodes have been
  added to the mst */
  while (queue.minimum() !== undefined) {
    /* here we extract the edge with the smallest weight, on the first iteration
    that will always be the root node */
    let u = queue.extractMin()
    /* we then loop through all the nodes, v, that are connected to u, we check to
    make sure we have not completed v already, and we make sure that
    taking that edge is more effiecent than the edge that we already have for v */
    for (let v = 0; v < matrix[u].length; v++) {
      if (matrix[u][v] !== 0 && visted[v] === false && matrix[u][v] < key[v]) {
        /* if taking this edge is more effiecent we update the key of v, update
        the priority queue, and set the pred of v, as u */
        key[v] = matrix[u][v]
        for (let i = 0; i < matrix.length; i++) {
          if (queue.array[i].data === v) {
            queue.decreaseKey(i, key[v])
          }
        }
        pred[v] = u
      }
      /* Once we have visted the nodes connected to u, we mark u as visted */
      visted[u] = true
    }
  }
  /* the answer list will be a list of the edges in the MST, we generate this
  list from the pred list */
  let answer = []
  /* in this for loop we loop through the pred list, creating a new list with
  two values, the node index, and the node that links that node to the MST.
  This generates a list of all the edges in the MST */
  for (let i = 0; i < matrix.length; i++) {
    answer.push([i, pred[i]])
  }

  /* the output of the Prim's Algorithm is a preorder walk through the MST, that
  DFS generates */
  return dfs(answer)
}


/* Export prim function to express server. This allows the server to access all exported functions
freely. The TPSAlgorithm.js is then loaded as an object in the server file where prim is called.*/
module.exports = { prim }

