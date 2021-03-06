#define _CRT_SECURE_NO_WARNINGS

// This header file defines the public API for Google Test.
//It should be included by any test program that uses Google Test.
#include "gtest/gtest-spi.h"

#include "koala/graph/graph.h"

/* TEST(test_case_name, test_name) is a predefined macro.
These are ordinary C++ functions that don't return a value.
In this function, along with any valid C++ statements you want to include,
use the various Google Test assertions to check values.
The test's result is determined by the assertions;
if any assertion in the test fails (either fatally or non-fatally),
or if the test crashes, the entire test fails. Otherwise, it succeeds.
*/

using namespace std;
using namespace Koala;

const int N = 7;

class GraphTest : public ::testing::Test {

public:

	typedef Graph<char, string> MyGraph;
	typedef Graph<char, int, GrDefaultSettings<EdUndir, false> > MyGraph2;

	MyGraph g;
	MyGraph::PVertex V[N];

	MyGraph2 g2;
	MyGraph2::PVertex V2[N];

	void createGraph()
	{
		V[0] = g.addVert('A'), V[1] = g.addVert('B'), V[2] = g.addVert('C'), V[3] = g.addVert('D');
		V[4] = g.addVert('E'), V[5] = g.addVert('F'), V[6] = g.addVert('G');

		g.addEdge(V[0], V[2], "ac"), g.addArc(V[0], V[2], "ac2"), g.addEdge(V[0], V[3], "ad"),
			g.addArc(V[0], V[5], "af"), g.addArc(V[0], V[6], "ag"), g.addEdge(V[0], V[6], "ag2"),
			g.addLoop(V[1], "b"), g.addLoop(V[1], "b2"), g.addArc(V[1], V[2], "bc"),
			g.addEdge(V[1], V[4], "be"), g.addEdge(V[1], V[5], "bf"), g.addEdge(V[1], V[6], "bg"),
			g.addEdge(V[2], V[0], "ca"), g.addEdge(V[2], V[3], "cd"), g.addArc(V[2], V[4], "ce"),
			g.addEdge(V[3], V[4], "de"), g.addLoop(V[4], "e");
	}

	void createGraph2()
	{
		V2[0] = g2.addVert('A'), V2[1] = g2.addVert('B'), V2[2] = g2.addVert('C'), V2[3] = g2.addVert('D');
		V2[4] = g2.addVert('E'), V2[5] = g2.addVert('F'), V2[6] = g2.addVert('G');

		g2.addEdge(V2[0], V2[2]), g2.addEdge(V2[0], V2[3]), g2.addEdge(V2[0], V2[5]), g2.addEdge(V2[0], V2[6]),
			g2.addEdge(V2[1], V2[2]), g2.addEdge(V2[1], V2[4]), g2.addEdge(V2[1], V2[5]), g2.addEdge(V2[1], V2[6]),
			g2.addEdge(V2[2], V2[3]), g2.addEdge(V2[2], V2[4]), g2.addEdge(V2[3], V2[4]);
	}
};

TEST_F(GraphTest, MethodAdjMatrixTest)
{
	createGraph();
	createGraph2();

	EXPECT_EQ(true, g.allowedAdjMatrix());
	EXPECT_EQ(false, g2.allowedAdjMatrix());

	g.reserveAdjMatrix(N - 1);
	g2.reserveAdjMatrix(N - 1);

	EXPECT_EQ(false, g.hasAdjMatrix());
	EXPECT_EQ(false, g2.hasAdjMatrix());
	EXPECT_EQ(true, g.makeAdjMatrix());
	EXPECT_EQ(false, g2.makeAdjMatrix());
	EXPECT_EQ(true, g.hasAdjMatrix());
	EXPECT_EQ(false, g2.hasAdjMatrix());
	EXPECT_EQ(true, g.delAdjMatrix());
	EXPECT_EQ(false, g.delAdjMatrix());
	EXPECT_EQ(false, g.hasAdjMatrix());
	EXPECT_EQ(false, g2.hasAdjMatrix());
}

TEST_F(GraphTest, MethodsClearClearEdgesTest)
{
	createGraph();
	EXPECT_EQ(7, g.getVertNo());
	EXPECT_EQ(17, g.getEdgeNo());
	g.clearEdges();
	EXPECT_EQ(7, g.getVertNo());
	EXPECT_EQ(0, g.getEdgeNo());
	g.clear();
	EXPECT_EQ(0, g.getVertNo());
	EXPECT_EQ(0, g.getEdgeNo());
}

//TEST_F(GraphTest, MethodClearTest)
//{
//	createGraph();
//
//	g.
//
//	//EXPECT_EQ(, );
//}
