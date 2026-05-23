(function_definition
  declarator: (function_declarator
    declarator: (identifier) @name)) @func

(struct_specifier name: (type_identifier) @name) @struct_def

(type_definition
  declarator: (type_identifier) @name) @tdef

(enum_specifier name: (type_identifier) @name) @enm

(preproc_include
  path: (_) @name) @imp
