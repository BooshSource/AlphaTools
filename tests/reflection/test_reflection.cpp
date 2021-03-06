
#include "test_reflection.h"
#include "at_tests"
#include "at_reflect"


using namespace reflect;


class TestClass {
public:
    
    static float f;
    
    int a = 5;
    TestClass* b = nullptr;
    
    TestClass() = default;
    
    TestClass(int a, TestClass* b) {
        this->a = a;
        this->b = b;
    }
    
    explicit operator int() {
        return a;
    }
    
    ~TestClass() = default;
    
    static void static_decrement() {
        f--;
    }
    
    static float static_multiply(float factor) {
        return f*factor;
    }
    
    void increment() {
        a++;
    }
    
    int multiply(int factor) {
        return a * factor;
    }
    
};

float TestClass::f = .5f;


DECLARE_TYPE(reflect::Type**)
DECLARE_TYPE(TestClass)
DECLARE_TYPE(TestClass*)

DECLARE_CONSTRUCTOR(TestClass, int, TestClass*)

DECLARE_MEMBER_DATA(TestClass, a)
DECLARE_MEMBER_DATA(TestClass, b)
DECLARE_MEMBER_FUNC(TestClass, increment)
DECLARE_MEMBER_FUNC(TestClass, multiply)

DECLARE_STATIC_DATA(TestClass, f)
DECLARE_STATIC_FUNC(TestClass, static_decrement)
DECLARE_STATIC_FUNC(TestClass, static_multiply)

DECLARE_TYPE_CAST(TestClass, int)


void test_construction() {
    Type* t = Type::from<TestClass>();
    
    std::vector<Constructor*> constructors = t->get_constructors();
    
    Constructor* c1 = t->get_constructor({});
    ASSERT(c1 != nullptr);
    Constructor* c2 = t->get_constructor({Type::from<int>(), Type::from<TestClass*>()});
    ASSERT(c2 != nullptr);
    
    TestClass tc1 = c1->construct({}).get_value_ref<TestClass>();
    TestClass tc2 = c2->construct(
        {Variant::from_instance(1), Variant::from_instance(&tc1)}
    ).get_value_ref<TestClass>();
    
    ASSERT(tc1.a == 5, "TestClass a wasn't default");
    ASSERT(tc1.b == nullptr, "TestClass b wasn't default");
    
    ASSERT(tc2.a == 1, "TestClass a wasn't 1");
    ASSERT(tc2.b == &tc1, "TestClass b wasn't tc1");
}

void test_member_data() {
    Type* t = Type::from<TestClass>();
    
    Constructor* c = t->get_constructor({Type::from<int>(), Type::from<TestClass*>()});
    
    TestClass tc = c->construct(
        {Variant::from_instance(-10), Variant::from_instance((TestClass*)nullptr)}
    ).get_value_ref<TestClass>();
    
    MemberProperty* mp = t->get_property("a");
    MemberProperty* mp2 = t->get_property("b");
    
    int a = mp->get(Variant::from_ref(tc)).get_value<int>();
    ASSERT(a == tc.a, "Get a didn't work");
    
    TestClass* b = mp2->get(Variant::from_ref(tc)).get_value<TestClass*>();
    ASSERT(b == tc.b, "Get b didn't work");
    
    mp->set(Variant::from_ref(tc), Variant::from_instance(10));
    ASSERT(tc.a == 10, "Set a didn't work");
    mp2->set(Variant::from_ref(tc), Variant::from_instance(&tc));
    ASSERT(tc.b == &tc, "Set b didn't work");
    
    // TODO: assert throws tests for type safety
}

void test_member_function() {
    Type* t = Type::from<TestClass>();
    
    TestClass tc = t->get_constructor({})->construct({}).get_value_ref<TestClass>();
    
    ASSERT(tc.a == 5);
    t->get_function("increment", {})->invoke(Variant::from_ref(tc), {});
    ASSERT(tc.a == 6, "Function wasn't called correctly");
    
    MemberFunction* multiply = t->get_function("multiply", {Type::from<int>()});
    int result = multiply->invoke(Variant::from_ref(tc), {Variant::from_instance(2)}).get_value_ref<int>();
    ASSERT(result == 12, "Multiply function returned incorrect value");
    result = multiply->invoke(Variant::from_ref(tc), {Variant::from_instance(5)}).get_value_ref<int>();
    ASSERT(result == 30, "Multiply function returned incorrect value");
}

void test_static_data() {
    Type* t = Type::from<TestClass>();
    
    StaticProperty* sp = t->get_static_property("f");
    
    float f = sp->get().get_value<float>();
    ASSERT(f == TestClass::f);
    
    sp->set(Variant::from_instance(1.f));
    ASSERT(TestClass::f == 1.f);
    sp->set(Variant::from_instance(.5f));
    ASSERT(TestClass::f == .5f);
}

void test_static_function() {
    Type* t = Type::from<TestClass>();
    
    ASSERT(TestClass::f == .5f);
    
    StaticFunction* decrement = t->get_static_function("static_decrement");
    decrement->invoke({});
    ASSERT(TestClass::f == -.5f);
    
    StaticFunction* multiply = t->get_static_function("static_multiply");
    float result = multiply->invoke({Variant::from_instance(5.f)}).get_value<float>();
    ASSERT(result == -2.5f);
    result = multiply->invoke({Variant::from_instance(2.f)}).get_value<float>();
    ASSERT(result == -1.f);
}

void test_destruction() {
    Type* t = Type::from<TestClass>();
    
    TestClass* tc = new TestClass();
    
    t->get_destructor()->destruct(Variant::from_ptr(tc));
}

void test_pointer_shift() {
    Type* p_type = Type::from_name("reflect::Type*");
    Type* type = Type::from_name("reflect::Type");
    
    ASSERT(p_type->remove_pointer() == type);
    ASSERT(type->add_pointer() == p_type);
    
    Variant v_type = Variant::from_ptr(&type);
    Variant v_type2 = p_type->get_caster()->remove_pointer(v_type);
    
    ASSERT(v_type.get_type() == p_type);
    ASSERT(v_type2.get_type() == type);
}

void test_fully_variant() {
    Type* int_type = Type::from_name("int");
    Type* tc_type = Type::from_name("TestClass");
    
    Variant int_instance = int_type->get_default_constructor()->construct();
    Variant tc_instance = tc_type->get_constructor({})->construct({});
    
    tc_type->get_property("a")->set(tc_instance, int_instance);
    
    Variant a_value = tc_type->get_property("a")->get(tc_instance);
    
    ASSERT(a_value.get_value_ref<int>() == 0); // This is the only place we actually use non-reflection a type!
    
    tc_type->get_function("increment", {})->invoke(tc_instance, {});
    
    ASSERT(a_value.get_value_ref<int>() == 1);
    
    Variant multiply_result = tc_type->get_function("multiply", {Type::from<int>()})->invoke(tc_instance, {int_instance});
    
    ASSERT(multiply_result.get_value_ref<int>() == 0);
    
    // We don't want to destruct them manually, as they're 'owned' and as such destruct themselves
}

void run_reflection_tests() {
    TEST(test_construction)
    TEST(test_member_data)
    TEST(test_member_function)
    TEST(test_static_data)
    TEST(test_static_function)
    TEST(test_destruction)
    TEST(test_pointer_shift)
    
    TEST(test_fully_variant)
}
