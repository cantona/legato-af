{#-
 #  Jinja2 template for generating C prototypes for Legato APIs.
 #
 #  Note: C/C++ comments apply to the generated code.  For example this template itself is not
 #  autogenerated, but the comment is copied verbatim into the generated file when the template is
 #  expanded.
 #
 #  Copyright (C) Sierra Wireless Inc.
 #}
/*
 * ====================== WARNING ======================
 *
 * THE CONTENTS OF THIS FILE HAVE BEEN AUTO-GENERATED.
 * DO NOT MODIFY IN ANY WAY.
 *
 * ====================== WARNING ======================
 */
{% block HeaderComments %}
{% endblock %}
#ifndef {{apiName|upper}}_INTERFACE_H_INCLUDE_GUARD
#define {{apiName|upper}}_INTERFACE_H_INCLUDE_GUARD


#include "legato.h"
{%- block InterfaceHeader %}{%- if imports %}

// Interface specific includes
{%- for import in imports %}
#include "{{import}}.h"
{%- endfor %}
{%- endif %}
{%- endblock %}


{% block GenericFunctions %}{% endblock %}
{% for define in definitions %}

//--------------------------------------------------------------------------------------------------
{{define.comment|FormatHeaderComment}}
//--------------------------------------------------------------------------------------------------
#define {{apiName|upper}}_{{define.name}} {{define.value}}
{%- endfor %}
{%- for type in types if type is not HandlerType %}

//--------------------------------------------------------------------------------------------------
{{type.comment|FormatHeaderComment}}
//--------------------------------------------------------------------------------------------------
{%- if type is EnumType %}
typedef enum
{
    {%- for element in type.elements %}
    {{apiName|upper}}_{{element.name}} = {{element.value}}{%if not loop.last%},{%endif%}
        ///<{{element.comments|join("\n///<")|indent(8)}}
    {%- endfor %}
}
{{type|FormatType}};
{%- elif type is BitMaskType %}
typedef enum
{
    {%- for element in type.elements %}
    {{apiName|upper}}_{{element.name}} = {{"0x%x" % element.value}}{%if not loop.last%},{%endif%}
    {%- if element.comments %}        ///<{{element.comments|join("\n///<")|indent(8)}}{%endif%}
    {%- endfor %}
}
{{type|FormatType}};
{%- elif type is ReferenceType %}
typedef struct {{apiName}}_{{type.name}}* {{type|FormatType}};
{%- endif %}
{% endfor %}
{%- for handler in types if handler is HandlerType %}{% block HandlerDeclaration scoped %}

//--------------------------------------------------------------------------------------------------
{{handler.comment|FormatHeaderComment}}
//--------------------------------------------------------------------------------------------------
typedef void (*{{handler|FormatType}})
(
    {%- for parameter in handler|CAPIParameters %}
    {{parameter|FormatParameter}}{% if not loop.last %},{% endif %}
        ///<{{parameter.comments|join("\n///<")|indent(8)}}
    {%-endfor%}
);
{%- endblock %}{%- endfor %}
{%- for function in functions %}{% block FunctionDeclaration scoped %}

//--------------------------------------------------------------------------------------------------
{{function.comment|FormatHeaderComment}}
//--------------------------------------------------------------------------------------------------
{{function.returnType|FormatType}} {{apiName}}_{{function.name}}
(
    {%- for parameter in function|CAPIParameters %}
    {{parameter|FormatParameter}}{% if not loop.last %},{% endif %}
        ///< [{{parameter.direction|FormatDirection}}]
             {{-parameter.comments|join("\n///<")|indent(8)}}
    {%-else%}
    void
    {%-endfor%}
);
{%- endblock %}{%- endfor %}

#endif // {{apiName|upper}}_INTERFACE_H_INCLUDE_GUARD
