#include "tlbf-tests.h"
#ifdef TLBF_CELL
#undef TLBF_CELL
#endif
#define TLBF_CELL (m_data.context->m_Cells[m_data.context->m_CurrentCell])
#define TLBF_CELLS(x,y) memcpy(m_data.context->m_Cells, x, y);
TEST(IncrementCell, Instructions, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 TLBF_CELL = 0;
	 ASSERT(tlbfBfIncrementCell(0) == TLBF_NO_CONTEXT);
	 ASSERT(tlbfBfIncrementCell(m_data.context) == TLBF_SUCCESS);
	 ASSERT(TLBF_CELL == 1);
	 ASSERT(tlbfBfIncrementCell(m_data.context) == TLBF_SUCCESS);
	 ASSERT(TLBF_CELL == 2);

     },
     {
	 tlbfContext* context;
     }
    );


TEST(DecrementCell, Instructions, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 TLBF_CELL = 5;
	 ASSERT(tlbfBfDecrementCell(0) == TLBF_NO_CONTEXT);
	 ASSERT(tlbfBfDecrementCell(m_data.context) == TLBF_SUCCESS);
	 ASSERT(TLBF_CELL == 4);
	 ASSERT(tlbfBfDecrementCell(m_data.context) == TLBF_SUCCESS);
	 ASSERT(TLBF_CELL == 3);

     },
     {
	 tlbfContext* context;
     }
    );

static tlbfCell testCells[4] = {0,1,2,3};

TEST(IncrementPtr, Instructions, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 m_data.context->m_CurrentCell = 0;
	 TLBF_CELLS(testCells, 4);
	 ASSERT(tlbfBfIncrementPtr(0) == TLBF_NO_CONTEXT);
	 ASSERT(tlbfBfIncrementPtr(m_data.context) == TLBF_SUCCESS);
	 ASSERT(m_data.context->m_CurrentCell == 1);
	 ASSERT(TLBF_CELL == 1);
	 ASSERT(tlbfBfIncrementPtr(m_data.context) == TLBF_SUCCESS);
	 ASSERT(m_data.context->m_CurrentCell == 2);
	 ASSERT(TLBF_CELL == 2);

     },
     {
	 tlbfContext* context;
     }
    );

TEST(DecrementPtr, Instructions, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 m_data.context->m_CurrentCell = 3;
	 TLBF_CELLS(testCells, 4);
	 ASSERT(tlbfBfDecrementPtr(0) == TLBF_NO_CONTEXT);
	 ASSERT(tlbfBfDecrementPtr(m_data.context) == TLBF_SUCCESS);
	 ASSERT(m_data.context->m_CurrentCell == 2);
	 ASSERT(TLBF_CELL == 2);
	 ASSERT(tlbfBfDecrementPtr(m_data.context) == TLBF_SUCCESS);
	 ASSERT(m_data.context->m_CurrentCell == 1);
	 ASSERT(TLBF_CELL == 1);

     },
     {
	 tlbfContext* context;
     }
    );



TEST(LoopStart, Instructions, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 static const char* program1 = "[]";
	 m_data.context->m_FreeLoopNode = &m_data.context->m_LoopNodes[0];
	 m_data.context->m_LastLoopNode = 0;
	 tlbfLoopNode* front;

	 ASSERT(tlbfBfLoopStart(0) == TLBF_NO_CONTEXT);

	 tlbfSetProgram(m_data.context, program1);
	 TLBF_CELLS(testCells, 4);
	 m_data.context->m_CurrentCell=0;
	 front = m_data.context->m_LastLoopNode;
	 ASSERT(tlbfBfLoopStart(m_data.context) == TLBF_SUCCESS);
	 ASSERT(front == m_data.context->m_LastLoopNode);
	 ASSERT(m_data.context->m_CurrentInstruction == &program1[1]);

	 tlbfSetProgram(m_data.context, program1);
	 TLBF_CELLS(testCells, 4);
	 m_data.context->m_CurrentCell=1;
	 front = m_data.context->m_LastLoopNode;
	 ASSERT(tlbfBfLoopStart(m_data.context) == TLBF_SUCCESS);
	 ASSERT(front != m_data.context->m_LastLoopNode);
	 ASSERT(m_data.context->m_LastLoopNode->m_LoopStart == &program1[0]);

	 static const char* program2 = "[[]]";

	 tlbfSetProgram(m_data.context, program2);
	 TLBF_CELLS(testCells, 4);
	 m_data.context->m_CurrentCell=0;
	 front = m_data.context->m_LastLoopNode;
	 ASSERT(tlbfBfLoopStart(m_data.context) == TLBF_SUCCESS);
	 ASSERT(front == m_data.context->m_LastLoopNode);
	 ASSERT(m_data.context->m_CurrentInstruction == &program2[3]);

	 static const char* program3 = "[[]";

	 tlbfSetProgram(m_data.context, program3);
	 TLBF_CELLS(testCells, 4);
	 m_data.context->m_CurrentCell=0;
	 front = m_data.context->m_LastLoopNode;
	 ASSERT(tlbfBfLoopStart(m_data.context) == TLBF_EOF);
	 ASSERT(front == m_data.context->m_LastLoopNode);

     },
     {
	 tlbfContext* context;
     }
    );

TEST(LoopEnd, Instructions, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 static const char* program1 = "[]";
	 m_data.context->m_FreeLoopNode = &m_data.context->m_LoopNodes[0];
	 m_data.context->m_LastLoopNode = 0;
	 tlbfLoopNode* front;

	 ASSERT(tlbfBfLoopEnd(0) == TLBF_NO_CONTEXT);

	 tlbfSetProgram(m_data.context, program1);
	 TLBF_CELLS(testCells,4);
	 m_data.context->m_CurrentCell = 1;
	 tlbfBfLoopStart(m_data.context);
	 front = m_data.context->m_LastLoopNode;
	 tlbfNext(m_data.context);
	 tlbfInstruction inst = m_data.context->m_CurrentInstruction;

	 m_data.context->m_CurrentInstruction = inst;
	 m_data.context->m_CurrentCell = 1;
	 ASSERT(tlbfBfLoopEnd(m_data.context) == TLBF_SUCCESS);
	 ASSERT(front == m_data.context->m_LastLoopNode);
	 ASSERT(m_data.context->m_CurrentInstruction == &program1[0]);

	 m_data.context->m_CurrentInstruction = inst;
	 m_data.context->m_CurrentCell = 0;
	 ASSERT(tlbfBfLoopEnd(m_data.context) == TLBF_SUCCESS);
	 ASSERT(front != m_data.context->m_LastLoopNode);
	 ASSERT(m_data.context->m_CurrentInstruction == &program1[1]);

     },
     {
	 tlbfContext* context;
     }
    );

TEST(Input, Instructions, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 TLBF_CELL = '\0';
	 InjectStdin("1");

	 ASSERT(tlbfBfInput(0) == TLBF_NO_CONTEXT);
	 ASSERT(tlbfBfInput(m_data.context) == TLBF_SUCCESS);
	 ASSERT(TLBF_CELL == '1');
     },
     {
	 tlbfContext* context;
     }
    );


TEST(Output, Instructions, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 TLBF_CELL = '1';
	 ClearStdout();
	 ASSERT(tlbfBfInput(0) == TLBF_NO_CONTEXT);
	 ASSERT(tlbfBfOutput(m_data.context) == TLBF_SUCCESS);
	 ASSERT(strcmp(GetStdout(), "1") == 0);
     },
     {
	 tlbfContext* context;
     }
    );

TEST(Cat, Smoke, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 static const char* program = ".[,.]";
	 static const char* input = "Hello, World!";
	 ClearStdout();

	 tlbfSetProgram(m_data.context, program);
	 tlbfRun(m_data.context);

	 ASSERT(strcmp(GetStdout(), input) == 0);
     },
     {
	 tlbfContext* context;
     }
    );
