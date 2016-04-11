<?

include("../../header.html");

?>

<h2>Programming 4</h2>

<hr>

<h3>Due Date: Dec. 7th</h3>

<hr>

<h3>Assignment</h3>

<p>
In this assignment, you are tasked with implementing the graph ADT using an
adjacency list implementation. As usual, there will be a code portion and a
report portion to this assignment.
</p>

<p>
In addition to the regular portions, you are allowed to do this assignment in
pairs. If you choose to have a partner, they must be from the same lab section
(unless otherwise approved), and you will be required to do more
implementation/reporting.
</p>

<h3>Code</h3>

<p>
At a minimum, you must implement the following for your graph:
<ul>
<li>Core ADT as found in the book. This means you need to allow for insertion
and removal of vertices and edges, implement all vertex and edge functions.
However, the design of the functions is up to you. Name your graph class "graph"
and place it in a file named "graph.h". Remember to create a test application so
you know your graph compiles and runs correctly.
Basic interface requirements are found <a href="graph.h">here</a> and described
below.
<ul>
<li>Graph takes two template parameters for vertex object and edge object types
and should contain internal classes for vertex and edge.</li>
<li>Vertices are referred to by a global vertex descriptor (size_t). Edges are
referred to by edge descriptors (pair&lt;size_t, size_t&gt;).</li>
<li>Typedefs should define descriptors, vertex iterators, edge iterators, and
adjacency edge iterators.</li>
<li>Basic accessors provided to properties, descriptors, begin/end iterators,
and finding vertices/edges based on descriptors.</li>
<li>Basic modifiers should be provided for inserting and removing vertices and
edges.</li>
</ul>
</li>
<li>Input/Output operators for your graph class. Use the following as
file specifications:
<h4>Example file:</h4>
<p>
<code>
5 4<br>
D<br>
E<br>
N<br>
N<br>
Y<br>
0 1 40<br>
3 4 23<br>
1 0 40<br>
4 3 23<br>
</code>
</p>
<h4>Specification</h4>
<p>
<code>
num_vertices num_edges<br>
vertex_0<br>
vertex_1<br>
...<br>
vertex_n<br>
edge_0<br>
edge_1<br>
...<br>
edge_m<br>
</code>
</p>
<p>
Note edges are formed as <code>v_i v_j weight</code>.
<a href="football.g">Here is a larger example file</a> for a
<code>graph&ltint, int&gt</code>.
</p>
</li>
<li>
Breadth-first Search Algorithm which labels the vertices and edges as discussed
in class and stores extra pointer information for the BFS tree. Interface for
the BFS function can be found in <a href="graph_algorithms.h">this algorithms
file</a>.
</li>
<li>Proper documentation of all classes and methods in Doxygen style comments
(as all of my code examples for you have done). Set up a Doxygen file (again use
mine as an example) to create automatic webpages (to be turned in with your
assignment). These can be created on <code>sun.cs.tamu.edu</code>.</li>
</li>
<li>If you decide to work with a partner you must also implement one of the MST or
SSSP algorithms for your graph. Interfaces for these functions can be found in
<a href="graph_algorithms.h">this algorithms file</a>.
</li>
</ul>

<h3>Report</h3>
<p>
For each algorithm you implement, test performance of your graph on a planar
mesh (each vertex has degree 4 essentially, it is basically a grid), a
complete graph, and a random connected graph (start with a connected line of
vertices, then add random edges). After doing base performance measures also
determine big-oh constants for the algorithm for mesh-input. The report should
include the following sections:
</p>
<ul>
<li>Introduction</li>
<li>Implementation details - Discuss design decisions of the graph</li>
<li>Theoretical Analysis - Discuss complexity of graph operations and
algorithms</li>
<li>Experimental Analysis - include setup, results, big-oh constants, and
discussion of results</li>
<li>Conclusion</li>
</ul>

<h3>Bonus</h3>
<p>
Each extra algorithm and graph implementation that is implemented and analyzed
can receive bonus points. Note if you are working in pairs, bonus points will be
split between partners. Interfaces for such extra functions should follow
<a href="graph_algorithms.h">this algorithms file</a>.

</p>

<h3>Competition</h3>
<p>
I am curious which person/team can create the best implementation of a graph.
Those wishing to participate in a competition can submit their graph.h and
graph_algorithms.h files the night before the due date (emailed to me). The
lecture period of, I will run a <a href="timing.cpp">live timing test</a> to see
which team generates the best graph implementation. The winner will receive a
special prize!
</p>
<ul>
<li>The graph.h must conform to the specifications given and must compile with
<a href="timing.cpp">my test code</a> in order to be able to participate in the
competition.</li>
<li>I will be performing random graph operations and algorithms (including
edge/vertex deletion).</li>
<li>Failure to complete the test/segfault will result in a disqualification.</li>
<li>
Top times (so far)
<ol>
<li><a href="dumb_vector_impl">Jory first implementation. Sizes: 300, 1750, 800</a></li>
</ol>
</li>
</ul>

<hr>

<?

include("grading.html");

?>

<?

include("../../footer.html");

?>
