#ifndef _Violation
#define _Violation

namespace GraphTypes
{
  namespace FlowTypes
  {

    class Violation
    {
    public:
      enum E_Violation{UNDEFINED, NOVIOLATION, CONSERVATION_VIOLATION, INTERNAL_NEUTRALITY_VIOLATION, FLOW_LIMITS_VIOLATION};

      Violation();
      Violation(const E_Violation & violationType);
      Violation(const Violation & violation);

      Violation & operator=(const Violation & violation);
      Violation & operator=(const E_Violation & violationType);

      bool operator==(const Violation & violation)const;
      bool operator==(const E_Violation & violationType)const;
      bool operator!=(const Violation & violation)const;
      bool operator!=(const E_Violation & violationType)const;

      friend bool operator==(const E_Violation & violationType, const Violation & violation);

      friend bool operator!=(const E_Violation & violationType, const Violation & violation);

      std::string toString()const;
      const E_Violation & violationType()const;

    private:
      E_Violation _violationType;
    };

  }
}

#endif
