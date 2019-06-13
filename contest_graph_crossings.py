from input_functions import *
from arrangement_based_crossing_computation import *
import time
from edge_crossing import *

#file_name = 'input14.txt'
file_name = 'input16.txt'

start_time = time.time()
n, node_coords, edge_list = take_input(file_name)
x = [node_coords[i][0] for i in range(len(node_coords))]
y = [node_coords[i][1] for i in range(len(node_coords))]
edg_u = [edge_list[i][0] for i in range(len(edge_list))]
edg_v = [edge_list[i][1] for i in range(len(edge_list))]
res = get_edge_crossings(n, x, y, edg_u, edg_v)
#print(res)
count = 0
for i in range(len(res)):
  for j in res[i]:
    if i>j:continue
    edge1 = edge_list[i]
    edge2 = edge_list[j]
    #if not share_vertex(edge1, edge2):
    if(doIntersect(node_coords[edge1[0]][0], node_coords[edge1[0]][1], node_coords[edge1[1]][0], node_coords[edge1[1]][1], node_coords[edge2[0]][0], node_coords[edge2[0]][1], node_coords[edge2[1]][0], node_coords[edge2[1]][1])):
      count = count + 1
print('n: ', n, 'm: ', len(edge_list), 'count: ', count)
print('Time taken by cgal: ', (time.time() - start_time), ' seconds')

start_time = time.time()
n, node_coords, edge_list = take_input(file_name)
count = 0
for i in range(len(edge_list)):
  for j in range(i+1,len(edge_list)):
   edge1 = edge_list[i]
   edge2 = edge_list[j]
   #if not share_vertex(edge1, edge2):
   if(doIntersect(node_coords[edge1[0]][0], node_coords[edge1[0]][1], node_coords[edge1[1]][0], node_coords[edge1[1]][1], node_coords[edge2[0]][0], node_coords[edge2[0]][1], node_coords[edge2[1]][0], node_coords[edge2[1]][1])):
    count = count + 1
#print('n: ', n, 'm: ', len(edge_list), 'count: ', count)
print('Time taken by naive: ', (time.time() - start_time), ' seconds')


