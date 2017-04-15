#include "tlbf-tests.h"

TEST(InitTerminate, Basic, 0.0f,
     // initialisation
     {
	 m_data.context = 0;
     },
     // cleanup
     {
	 tlbfTerminateContext(&m_data.context);
     },
     // test
     {
	 ASSERT(tlbfInitContext(&m_data.context) == TLBF_SUCCESS);
      ASSERT(m_data.context != 0);
	 ASSERT(tlbfTerminateContext(&m_data.context) == TLBF_SUCCESS);
      ASSERT(m_data.context == 0)
     },
     // data
     {
	 tlbfContext* context;
     }
    );


TEST(SetProgram, Basic, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 static const char* program = "";
	 m_data.context->m_Program = 0;
	 ASSERT(tlbfSetProgram(m_data.context, program) == TLBF_SUCCESS);
	 ASSERT(m_data.context->m_Program == program);
	 ASSERT(m_data.context->m_CurrentInstruction == program);
     },
     {
	 tlbfContext* context;
     }
    );

TEST(Run, Basic, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 static const char* program = "";
	 tlbfSetProgram(m_data.context, program);
	 ASSERT(tlbfRun(m_data.context) == TLBF_SUCCESS);
     },
     {
	 tlbfContext* context;
     }
    );

TEST(Next, Internal, 0.0f,
     {
	 tlbfInitContext(&m_data.context);
     },
     {
	 tlbfTerminateContext(&m_data.context);
     },
     {
	 static const char* program = "123";
         tlbfSetProgram(m_data.context, program);
	 ASSERT(tlbfNext(0) == TLBF_NO_CONTEXT);
	 ASSERT(tlbfNext(m_data.context) == TLBF_SUCCESS);
	 ASSERT(m_data.context->m_CurrentInstruction == &program[1]);
	 ASSERT(tlbfNext(m_data.context) == TLBF_SUCCESS);
	 ASSERT(m_data.context->m_CurrentInstruction == &program[2]);
	 ASSERT(tlbfNext(m_data.context) == TLBF_EOF);
     },
     {
	 tlbfContext* context;
     }
    );

	 
