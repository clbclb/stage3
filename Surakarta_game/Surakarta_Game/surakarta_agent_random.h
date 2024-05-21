#include <memory>
#include "surakarta_agent_base.h"
#include "widget.h"
class SurakartaAgentRandom : public SurakartaAgentBase {
   public:
    using SurakartaAgentBase::SurakartaAgentBase;
    SurakartaMove CalculateMove() override;
};
