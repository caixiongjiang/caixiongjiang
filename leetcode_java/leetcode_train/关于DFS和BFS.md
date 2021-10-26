# 图的遍历：DFS和BFS算法
DFS从字面上来说就是搜的越深越好，BFS就是搜的越广越好！

示例：
```
    3
   / \
  9  20
 /  /  \
10 15   7
```
DFS顺序：3 9 10 20 15 7

BFS顺序：3 9 20 10 15 7

## 一般搜索算法的流程框架
* 1.定义点集X为已经处理的点，点集F为已发现但尚未处理的点
* 2.初始化点集X为空，点集F只包含搜索的起点
* 3.只要点集F不为空，循环4~6：
* 4.从点集F中取出一个,点v
* 5.处理点v，把点v加入点集X
* 6.遍历v的出边，对于每个v的邻居，若既不在点集X中也不在点集F中，则加入点集F
* 7.搜索结束，点集义里的点是搜索过的点

代码框架如下：
```c++
bool discovered[10001];
stack<int> F;
//queue<int> F;
void search(){
	F.push(1);
	discovered[1] = true;
	while(!F.empty()){
		int id = F.top();
		//int id=F.front(0) ;
		F.pop();
		cout << id <<' ';
		EDGE *e = nodes[id].fir;
		while(e != NULL) {
			if (!discovered[e->v]){
				F.push(e->v);
				discovered[e-›v] = true;
			}
			e = e->nex;//代表相邻的未发现的点
		}
	}
}
```
## 深度优先搜索
深度优先搜索的步骤：在上述搜索算法的流程框架中修改即可。

**若第4步的点集F为栈（后进先出），则算法为DFS。**

代码见**一般搜索框架**

### 递归DFS的流程框架
* 1.定义点集X为已经处理的点(visited[])
* 2.初始化,点集X为空
* 3.递归搜索点v(开始时搜索起点)：
* 4.处理点v，把点v加入点集x
* 5.遍历v的出边，对于每个v的邻居，若既不在点集X中，则递归处理那个点
* 6.搜索结束，点集X里的点是搜索过的点

代码框架如下：
```c++
bool visited[10001];
void DFS(int id){
	visited[id] = true;
	cout << id << ' ';
	EDGE *e = nodes[id].fir;
	while (e != NULL){
		if(!visited[e->v]) DFS(e->v);
		e = e->nex;
	}
}
```
### 栈的DFS与递归DFS的小区别
直接上示例:
```
    2——4
  / |
1   |
  \ |
    3
```
<span style="color:green">栈的DFS：3先被发现入栈，则3被访问的路径是1->3，处理的顺序不可能是1 2 3 4</span>

<span style="color:green">递归DFS：3先被2递归探索，则3被访问的路径是1->2->3，处理顺序可能是1 2 3 4</span>

*注：若处理点与发现该点的路径有关，这两种方式带来的结果就会不同。*
## 广度优先搜索
深度优先搜索的步骤：在上述搜索算法的流程框架中修改即可。

**若第4步的点集F为队列（先进先出），则算法为BFS。**

代码见**一般搜索框架**